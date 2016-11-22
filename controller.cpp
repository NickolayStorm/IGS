#include "controller.h"
#include "transforms.h"
#include "tor.h"
#include "toruscurve.h"
#include "ennepersurface.h"
Controller* Controller::_self = nullptr;
Controller::Controller() : QObject(nullptr),
                           _mainWindow(Qt::red, Qt::white),
                           _viewer(10, 10, 10)
{
    Transforms().refreshMatrix(_viewer, 200);

    _shapes.insert(QString("Torus")          , [](){return new Tor();}           );
    _shapes.insert(QString("Torus curve")    , [](){return new TorusCurve();}    );
    _shapes.insert(QString("Enneper Surface"), [](){return new EnneperSurface();});

    // Actially we should use just "_shapes.keys()"
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

    connect(&_mainWindow, SIGNAL( slidersChanged(Point) ),
            this,           SLOT( slidersChanged(Point) )        );
    connect(&_mainWindow, SIGNAL( colorsChanged(QColor,QColor) ),
            this,           SLOT( colorsChanged(QColor,QColor) ) );
    connect(&_mainWindow, SIGNAL( isPaintedChanged(bool) ),
            this,           SLOT( isPaintedChangd(bool))         );
    connect(&_mainWindow, SIGNAL( uvChanged(int,int) ),
            this,           SLOT( uvChanged(int,int) )          );
    connect(&_mainWindow, SIGNAL( figureChanged(QString) ),
            this,           SLOT( figureChanged(QString))        );
    connect(&_mainWindow, SIGNAL( uvStepsChanged(int,int) ),
            this,           SLOT( uvStepsChanged(int,int))       );
    connect(&_mainWindow, SIGNAL( paramsChanged(int,int) ),
            this,           SLOT( paramsChanged(int,int))        );
}

void Controller::refreshFigures(){

    std::vector<std::vector<Point>> points;
    points.reserve(20);
    _plgns.clear();
    for(int i = 0; i < _uCount; ++i){
        std::vector<Point> subVec;
        subVec.reserve(_vCount);
        points.push_back(subVec);
        for(int j = 0; j < _vCount; ++j){
            points[i].push_back(_shape->pointOn(i, j));
            // TODO: remove this condition
            if (i > 0 && j > 0) {
                // Indexing like [i][j]
                std::cout << "Max indexing: " << i*_uCount + j << std::endl;
                _plgns.push_back(Polygon(points[i - 1][j-1],
                                         points[i - 1][j],
                                         points[i][j-1]));

                _plgns.push_back(Polygon(points[i][j-1],
                                         points[i - 1][j],
                                         points[i][j]));

            }
        }
    }
    std::cout << "u count: " << _uCount << std::endl;
}

void Controller::figureChanged(QString name){
    if(_shape != nullptr){
        delete _shape;
        _shape = nullptr;
    }

    auto ishape = _shapes.find(name);
    _shape = (*ishape)();

    auto maxes = _shape->getUVMax();
    auto currs = _shape->getInit();
    _mainWindow.setUVSliderParams(maxes.first, maxes.second,
                                  currs.first, currs.second);

    auto params = _shape->getParams();
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
    if(Controller::_self == nullptr){
        Controller::_self = new Controller();
    }

    return Controller::_self;
}

void Controller::slidersChanged(Point newViewer){
    _viewer = newViewer;
    // TODO: 200 to real center
    Transforms().refreshMatrix(_viewer, 200);
    _mainWindow.updateDrawingArea();
}

void Controller::colorsChanged(QColor inside, QColor outside){
    _backColor = outside;
    _frontColor = inside;
    _mainWindow.updateDrawingArea();
}

void Controller::isPaintedChangd(bool is){
    _isPainted = is;
    _mainWindow.updateDrawingArea();
}

void Controller::uvChanged(int u, int v){
    _shape->setUV(u, v);
    refreshFigures();
    _mainWindow.updateDrawingArea();
}

void Controller::uvStepsChanged(int u, int v){
    _uCount = u;
    _vCount = v;
    refreshFigures();
    _mainWindow.updateDrawingArea();
}

void Controller::paramsChanged(int fst, int snd){
    _shape->setParams(fst, snd);
    refreshFigures();
    _mainWindow.updateDrawingArea();
}

std::vector<Polygon>* Controller::getPolygons(){
    return &_plgns;
}

Controller::~Controller(){
    delete _shape;
}


