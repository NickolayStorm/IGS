#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "mainwindow.h"
#include "drawingarea.h"
#include "point.h"
#include <QObject>
#include "shape.h"
#include <vector>
#include "polygon.h"


class Controller : public QObject
{
    Q_OBJECT
public:
    static Controller* instance();
    inline Point getViewer(){return _viewer;}
//    std::vector<Point>* getPoints();
    std::vector<Polygon>* getPolygons();
private:
    std::vector<Point> _points;
    std::vector<Polygon> _plgns;
    void refreshFigures();
    void setShape(){}
    static Controller* _self;
    Controller();
    MainWindow _mainWindow;
    QSize _areaSize;
    Point _viewer;
    Shape* _shape;

signals:

public slots:
    void slidersChanged(Point);
};

#endif // CONTROLLER_H
