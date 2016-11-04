#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "mainwindow.h"
#include "drawingarea.h"
#include "point.h"
#include <QObject>
#include "shape.h"
#include <vector>

class Controller : public QObject
{
    Q_OBJECT
public:
    static Controller* instance();
    inline Point getViewer(){return _viewer;}
    std::vector<Point>* getPoints();
private:
    std::vector<Point> _points;
    static Controller* _self;
    Controller();
    MainWindow _mainWindow;
    Point _viewer;
    Shape* _shape;

signals:

public slots:
    void slidersChanged(Point);
};

#endif // CONTROLLER_H
