#include "controller.h"
#include "transforms.h"
#include "tor.h"
#include "toruscurve.h"
#include "ennepersurface.h"

// Fuck you and your singleton
#define DO_ONCE(...) { static bool _do_once_ = ([&](){ __VA_ARGS__ }(), true); (void)_do_once_; }

Controller* Controller::_self = nullptr;
Controller::Controller() : QObject(nullptr),
                           _mainWindow(Qt::red, Qt::white),
                           _viewer(10, 10, 10)
{
    _areaSize = _mainWindow.drawingAreaSize();
    Transforms::instance()->refreshMatrix(
                _viewer,
                _areaSize.width() / 2,
                _areaSize.height() / 2
                );

    _shapes.insert(QString("Torus")          , []{ return std::move(std::make_unique<Shape*>(new Tor())); }            );
    _shapes.insert(QString("Torus curve")    , []{ return std::move(std::make_unique<Shape*>(new TorusCurve())); }     );
    _shapes.insert(QString("Enneper Surface"), []{ return std::move(std::make_unique<Shape*>(new EnneperSurface())); } );

    // Actually we should use just "_shapes.keys()"
    // But if we do that
    // We would have been the unrepresentative order of elements
    // And we are have to use some dificult and boring funcs, so:
    auto initList = QStringList{
            "Torus",
            "Torus curve",
            "Enneper Surface"
        };
    _mainWindow.setShapeNames(initList);

    _plgns.reserve(400);
    _frontColor = Qt::red;
    _backColor = Qt::white;
    _isPainted = false;

    _pixMap = std::make_unique<QImage*>(new QImage(_areaSize, QImage::Format_RGB32));

    _zBuffer.resize(_areaSize.width() * _areaSize.height(),
                    std::numeric_limits<int>::min());

    _mainWindow.show();
    figureChanged("Torus");

    connect(&_mainWindow, SIGNAL( colorsChanged(QColor,QColor) ),
            this,           SLOT( colorsChanged(QColor,QColor) ) );
    connect(&_mainWindow, SIGNAL( isPaintedChanged(bool) ),
            this,           SLOT( isPaintedChangd(bool))         );
    connect(&_mainWindow, SIGNAL( uvChanged(int,int) ),
            this,           SLOT( uvChanged(int,int) )           );
    connect(&_mainWindow, SIGNAL( figureChanged(QString) ),
            this,           SLOT( figureChanged(QString))        );
    connect(&_mainWindow, SIGNAL( uvStepsChanged(int,int) ),
            this,           SLOT( uvStepsChanged(int,int))       );
    connect(&_mainWindow, SIGNAL( paramsChanged(int,int) ),
            this,           SLOT( paramsChanged(int,int))        );
    connect(&_mainWindow, SIGNAL( viewerPosMoved(float,float) ),
            this,           SLOT( moveViewer(float,float) )      );
}

void Controller::refreshPoints(){

    Transforms &transforms = *Transforms::instance();
    auto mapPoint = [&](const Point& p){
            return transforms.transform(p);
    };

    _plgns = (*_shape)->getPolygons(mapPoint);

    refreshPolygonColors();
}

void Controller::refreshPolygonColors(){
    for(auto &p : _plgns){
        auto color = getPolygonColor(p);
        p.setColor(color);
    }
    refreshPixMap();
}

void Controller::refreshPixMap(){
    // Fill Z-buffer and pixMap
    (*_pixMap)->fill(Qt::black);
    std::fill(_zBuffer.begin(), _zBuffer.end(),
              std::numeric_limits<int>::min());

    for(auto &p : _plgns){
        polygonOnPixmap(p);
    }
}

void Controller::polygonOnPixmap(ColoredPolygon& plgn){
    auto points = plgn.getPoints();
    Point t0 = points[0];
    Point t1 = points[1];
    Point t2 = points[2];
    QColor color = plgn.getColor();

    if (t0.getY()==t1.getY() && t0.getY()==t2.getY())
        return;

    if (t0.getY()>t1.getY()) std::swap(t0, t1);
    if (t0.getY()>t2.getY()) std::swap(t0, t2);
    if (t1.getY()>t2.getY()) std::swap(t1, t2);

    int total_height = t2.getY() - t0.getY();

    for (int i = 0; i < total_height; i++) {
        bool second_half = i > t1.getY()-t0.getY() || t1.getY()==t0.getY();
        int segment_height = second_half ? t2.getY()-t1.getY() : t1.getY()-t0.getY();
        float alpha = (float)i / total_height;
        float beta  = (float)(i - (second_half ? t1.getY() - t0.getY() : 0)) / segment_height; // be careful: with above conditions no division by zero here
        Point A =               t0 + Point(t2 - t0) * alpha;
        Point B = second_half ? t1 + Point(t2 - t1) * beta : t0 + Point(t1-t0) * beta;

        if (A.getX()>B.getX())
            std::swap(A, B);

        for (int j=A.getX(); j<=B.getX(); j++) {
            float phi = B.getX()==A.getX() ? 1. : (float)(j-A.getX())/(float)(B.getX()-A.getX());
            Point P = A + Point(B - A) * phi;

            if(P.getX() < 0 || P.getX() > (*_pixMap)->width() ||
               P.getY() < 0 || P.getY() > (*_pixMap)->height())
                continue;

            int idx = P.getX() + P.getY()*_areaSize.width();
            if(idx < 0 || idx > (*_pixMap)->width()*(*_pixMap)->height())
                continue;
            if (_zBuffer[idx] < P.getZ()) {
                _zBuffer[idx] = P.getZ();
                (*_pixMap)->setPixelColor(P.getQPoint(), color);
            }
        }
    }
}

void Controller::figureChanged(QString name){
    auto iter_shape = _shapes.find(name);
    _shape = (*iter_shape)();

    auto maxes = (*_shape)->getUVMax();
    auto currs = (*_shape)->getInit();
    _mainWindow.setUVSliderParams(maxes.first, maxes.second,
                                  currs.first, currs.second);

    auto params = (*_shape)->getParams();
    _mainWindow.setFigureSliderParams(params.first, params.second);
    refreshPoints();
    _mainWindow.updateDrawingArea();
}

QColor Controller::getPolygonColor(Polygon &polygon){
    float cos = polygon.getCos();
    QColor col;
    if (cos < 0) {
        col = _backColor;
        cos = -cos;
    }else{
        col = _frontColor;
    }
    int r = col.red() * cos;
    int g = col.green() * cos;
    int b = col.blue() * cos;
    return QColor(r, g, b, 255);
}

Controller* Controller::instance(){
    DO_ONCE(
             Controller::_self = new Controller();
           )
    return Controller::_self;
}

void Controller::changeViewerPos(Point newViewer){
    _viewer = newViewer;
    // TODO: 200 to real center
    Transforms::instance()->refreshMatrix(
                _viewer,
                _areaSize.width() / 2,
                _areaSize.height() / 2
    );
    refreshPoints();
    _mainWindow.updateDrawingArea();
}

void Controller::moveViewer(float x, float y){
    Transforms &transforms = *Transforms::instance();
    // x and y are swapped becouse it is a magic
    transforms.rotateX(y);
    transforms.rotateY(x);
    refreshPoints();
    _mainWindow.updateDrawingArea();
}

void Controller::colorsChanged(QColor inside, QColor outside){
    _backColor = outside;
    _frontColor = inside;
    refreshPolygonColors();
    _mainWindow.updateDrawingArea();
}

void Controller::isPaintedChangd(bool is){
    _isPainted = is;
    refreshPoints();
    _mainWindow.updateDrawingArea();
}

void Controller::uvChanged(int u, int v){
    (*_shape)->setUV(u, v);
    refreshPoints();
    _mainWindow.updateDrawingArea();
}

void Controller::uvStepsChanged(int u, int v){
    (*_shape)->setStepCounts(u, v);
    refreshPoints();
    _mainWindow.updateDrawingArea();
}

void Controller::paramsChanged(int fst, int snd){
    (*_shape)->setParams(fst, snd);
    refreshPoints();
    _mainWindow.updateDrawingArea();
}

QImage* Controller::getPixmap(){
    return *_pixMap;
}

Controller::~Controller(){
}
