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
    std::vector<Polygon>* getPolygons();
    QColor getPolygonColor(Polygon&);
    inline bool isPainted(){return _isPainted;}
    ~Controller();
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
    QColor _frontColor;
    QColor _backColor;
    bool _isPainted;

signals:

public slots:
    void slidersChanged(Point);
    void colorsChanged(QColor, QColor);
    void isPaintedChangd(bool);
};

#endif // CONTROLLER_H
