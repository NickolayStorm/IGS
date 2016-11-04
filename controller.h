#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "mainwindow.h"
#include "drawingarea.h"
#include "point.h"
#include <QObject>

class Controller : public QObject
{
    Q_OBJECT
public:
    static Controller* instance();
    inline Point getViewer(){return _viewer;}
private:
    static Controller* _self;
    Controller();
    MainWindow _mainWindow;
    Point _viewer;
signals:

public slots:
    void slidersChanged(Point);
};

#endif // CONTROLLER_H
