#include "controller.h"
#include "tor.h"
Controller* Controller::_self = nullptr;
Controller::Controller() : QObject(nullptr), _viewer(10, 10, 10)
{
    _shape = new Tor();
    _points.reserve(400);
    for(int i = 0; i < 20; ++i){
        for(int j = 0; j < 20; ++j){
            _points.push_back(_shape->pointOn(i, j));
        }
    }

    _mainWindow.show();
    connect(&_mainWindow, SIGNAL(slidersChanged(Point)), this, SLOT(slidersChanged(Point)));
}

Controller* Controller::instance(){
    if(Controller::_self == nullptr){
        Controller::_self = new Controller();
    }

    return Controller::_self;
}

void Controller::slidersChanged(Point newViewer){
    _viewer = newViewer;
    _mainWindow.updateDrawingArea();
}

std::vector<Point>* Controller::getPoints(){
    return &_points;
}


