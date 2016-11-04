#include "controller.h"

Controller* Controller::_self = nullptr;
Controller::Controller() : QObject(nullptr), _viewer(10, 10, 10)
{
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


