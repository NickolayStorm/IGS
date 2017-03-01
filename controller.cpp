#include "controller.h"
#include "transforms.h"
#include "tor.h"
#include "toruscurve.h"
#include "ennepersurface.h"
#include "shell.h"
#include "migration.h"
#include <QTimer>
#include <QAbstractAnimation>

#define ANIMATION_FPS 30

#define ANIMAT_COUNT 30

// Fuck you and your singleton
#define DO_ONCE(...) { static bool _do_once_ = ([&](){ __VA_ARGS__ }(), true); (void)_do_once_; }

Controller* Controller::_self = nullptr;
Controller::Controller() : QObject(nullptr),
                           _mainWindow(Qt::red, Qt::blue),
                           _viewer(10, 10, 10),
                           _lightPos(100,200,200)
{
    _areaSize = _mainWindow.drawingAreaSize();
    Transforms::instance()->refreshMatrix(
                _viewer,
                _areaSize.width() / 2,
                _areaSize.height() / 2
                );

    _shapes.insert(QString("Shell")          , []{ return std::move(std::make_shared<Shape*>(new Shell())); }          );
    _shapes.insert(QString("Torus")          , []{ return std::move(std::make_shared<Shape*>(new Tor())); }            );
    _shapes.insert(QString("Torus curve")    , []{ return std::move(std::make_shared<Shape*>(new TorusCurve())); }     );
    _shapes.insert(QString("Enneper Surface"), []{ return std::move(std::make_shared<Shape*>(new EnneperSurface())); } );

    // Actually we should use just "_shapes.keys()"
    // But if we do that
    // We would have been the unrepresentative order of elements
    // And we are have to use some dificult and boring funcs, so:
    auto initList = QStringList{
            "Shell",
            "Torus",
            "Torus curve",
            "Enneper Surface"
        };
    _mainWindow.setShapeNames(initList);

    _plgns.reserve(400);
    _frontColor = Qt::red;
    _backColor = Qt::blue;
    _lightColor = Qt::white;

    _pixMap = std::make_unique<QImage*>(new QImage(_areaSize, QImage::Format_RGB32));

    _zBuffer.resize(_areaSize.width() * _areaSize.height(),
                    std::numeric_limits<int>::min());

    _mainWindow.show();

    // Init shape stuff
    _shape = (*(_shapes.find("Torus")))();
    setWindowSliders();
    refreshPoints();
    _mainWindow.updateDrawingArea();

    connect(&_mainWindow, &MainWindow::colorsChanged,
        this, &Controller::colorsChanged  );
    connect(&_mainWindow, &MainWindow::uvChanged,
        this, &Controller::uvChanged      );
    connect(&_mainWindow, &MainWindow::figureChanged,
        this, &Controller::figureChanged  );
    connect(&_mainWindow, &MainWindow::uvStepsChanged,
        this, &Controller::uvStepsChanged );
    connect(&_mainWindow, &MainWindow::paramsChanged,
        this, &Controller::paramsChanged  );
    connect(&_mainWindow, &MainWindow::viewerPosMoved,
        this, &Controller::moveViewer     );
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
//    _plgns[0].setColor(Qt::black);
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
    auto new_shape = (*(_shapes.find(name)))();
    _shape = std::make_shared<Shape*>(new Migration(_shape, new_shape, ANIMAT_COUNT));
    _mainWindow.setEnabled(false);
    animationStep();
}

void Controller::setWindowSliders(){
    auto maxes = (*_shape)->getUVMax();
    auto currs = (*_shape)->getInit();
    _mainWindow.setUVSliderParams(maxes.first, maxes.second,
                                  currs.first, currs.second);

    auto params = (*_shape)->getParams();
    _mainWindow.setFigureSliderParams(params.first, params.second);
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
//    float lightCos = _lightPos.getCos(polygon.getNormal());
//    if(lightCos < 0){
//        lightCos = - lightCos;
//    }
    int r = col.red() * cos; // * lightCos;
    int g = col.green() * cos; // * lightCos;
    int b = col.blue() * cos; // * lightCos;
    return QColor(r, g, b, 255);
}

Controller* Controller::instance(){
    DO_ONCE(
             Controller::_self = new Controller();
           )
    return Controller::_self;
}

void Controller::changeLightPos(int x, int y, int z){
    _lightPos = Point(x, y, z);
    refreshPolygonColors();
    _mainWindow.updateDrawingArea();
}

void Controller::moveViewer(float x, float y){
    Transforms &transforms = *Transforms::instance();
    // x and y are swapped because it is a magic
    transforms.rotateX(y);
    transforms.rotateY(x);
    refreshPoints();
    _mainWindow.updateDrawingArea();
}

void Controller::colorsChanged(QColor inside, QColor outside){
    _backColor  = outside;
    _frontColor = inside;
    refreshPolygonColors();
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

void Controller::animationStep(){

    Migration* m = dynamic_cast<Migration*>(*_shape);
    m->step();
    if(!m->isFinished()){
        QTimer::singleShot(1000/ANIMATION_FPS, this, &Controller::animationStep);
    }else{
        _shape = m->getFinalShape();
        setWindowSliders();
        _mainWindow.setEnabled(true);
    }
    refreshPoints();
    _mainWindow.updateDrawingArea();
}

QImage* Controller::getPixmap(){
    return *_pixMap;
}

Controller::~Controller(){
}
