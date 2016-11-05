#include "controller.h"
#include "transforms.h"
#include "tor.h"
Controller* Controller::_self = nullptr;
Controller::Controller() : QObject(nullptr), _viewer(10, 10, 10)
{
    Transforms().refreshMatrix(_viewer, 240);
    _shape = new Tor();
    _points.reserve(400);
    _plgns.reserve(400);
    refreshFigures();
    _mainWindow.show();
    connect(&_mainWindow, SIGNAL(slidersChanged(Point)), this, SLOT(slidersChanged(Point)));
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

std::vector<Polygon>* Controller::getPolygons(){
    return &_plgns;
}


