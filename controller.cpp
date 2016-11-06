#include "controller.h"
#include "transforms.h"
#include "tor.h"
Controller* Controller::_self = nullptr;
Controller::Controller() : QObject(nullptr),
                           _mainWindow(Qt::red, Qt::white),
                           _viewer(10, 10, 10)
{
    Transforms().refreshMatrix(_viewer, 240);
    _shape = new Tor();
    _points.reserve(400);
    _plgns.reserve(400);
    _frontColor = Qt::red;
    _backColor = Qt::white;
    _isPainted = false;
//    _mainWindow(_frontColor, _backColor);
    refreshFigures();
    _mainWindow.show();
    connect(&_mainWindow, SIGNAL(slidersChanged(Point)), this, SLOT(slidersChanged(Point)));
    connect(&_mainWindow, SIGNAL(colorsChanged(QColor,QColor)), this, SLOT(colorsChanged(QColor,QColor)));
    connect(&_mainWindow, SIGNAL(isPaintedChanged(bool)), this, SLOT(isPaintedChangd(bool)));
}

void Controller::refreshFigures(){
    for(int i = 0; i < 20; ++i){
        for(int j = 0; j < 20; ++j){
            _points.push_back(_shape->pointOn(i, j));
            // TODO: remove this condition
            if (i > 0 && j > 0) {
                _plgns.push_back(Polygon(_points[(i - 1)*20 + j-1],
                                         _points[(i - 1)*20 + j],
                                         _points[i*20 + j-1]));

                _plgns.push_back(Polygon(_points[i*20 + j-1],
                                         _points[(i - 1)*20 + j],
                                         _points[i*20 + j]));

            }
        }
    }
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
    // TODO: 240 to real center
    Transforms().refreshMatrix(_viewer, 240);
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

std::vector<Polygon>* Controller::getPolygons(){
    return &_plgns;
}

Controller::~Controller(){
    delete _shape;
}


