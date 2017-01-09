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
    Transforms::instance()->refreshMatrix(_viewer, 200);

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
    _uCount = 20;
    _vCount = 20;

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

void Controller::refreshFigures(){

    std::vector<std::vector<Point>> points;
    points.reserve(20);
    _plgns.clear();
    Transforms &transforms = *Transforms::instance();
    for(int i = 0; i < _uCount; ++i){
        std::vector<Point> subVec;
        subVec.reserve(_vCount);
        points.push_back(subVec);
        for(int j = 0; j < _vCount; ++j){
            points[i].push_back((*_shape)->pointOn(i, j));
            // TODO: remove this condition
            if (i > 0 && j > 0) {
                Polygon one(  transforms.transform(points[i - 1][j - 1])
                            , transforms.transform(points[i - 1][j])
                            , transforms.transform(points[i][j-1]) );
                _plgns.push_back(one);
                Polygon two( transforms.transform(points[i][j - 1])
                           , transforms.transform(points[i - 1][j])
                           , transforms.transform(points[i][j]) );
                _plgns.push_back(two);
            }
        }
    }
    if(_isPainted){
        std::sort(_plgns.begin(), _plgns.end(),
                  [](auto &one, auto &two) -> bool {
            return one.getAverageZ() < two.getAverageZ();
        }
        );
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
    refreshFigures();
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
    Transforms::instance()->refreshMatrix(_viewer, 200);
    refreshFigures();
    _mainWindow.updateDrawingArea();
}

void Controller::moveViewer(float x, float y){
    Transforms &transforms = *Transforms::instance();
    // x and y are swapped becouse it is a magic
    transforms.rotateX(y);
    transforms.rotateY(x);
    refreshFigures();
    _mainWindow.updateDrawingArea();
}

void Controller::colorsChanged(QColor inside, QColor outside){
    _backColor = outside;
    _frontColor = inside;
    _mainWindow.updateDrawingArea();
}

void Controller::isPaintedChangd(bool is){
    _isPainted = is;
    refreshFigures();
    _mainWindow.updateDrawingArea();
}

void Controller::uvChanged(int u, int v){
    (*_shape)->setUV(u, v);
    refreshFigures();
    _mainWindow.updateDrawingArea();
}

void Controller::uvStepsChanged(int u, int v){
    _uCount = u;
    _vCount = v;
    (*_shape)->setStepCounts(u, v);
    refreshFigures();
    _mainWindow.updateDrawingArea();
}

void Controller::paramsChanged(int fst, int snd){
    (*_shape)->setParams(fst, snd);
    refreshFigures();
    _mainWindow.updateDrawingArea();
}

std::vector<Polygon>* Controller::getPolygons(){
    return &_plgns;
}

Controller::~Controller(){
}


