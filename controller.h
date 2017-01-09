#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "mainwindow.h"
#include "drawingarea.h"
#include "point.h"
#include <QObject>
#include <QMap>
#include <functional>
#include "shape.h"
#include <vector>
#include "polygon.h"
#include <memory>

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
    std::vector<std::vector<Point>> _points;
    std::vector<Polygon> _plgns;
    void refreshFigures();
    static Controller* _self;
    Controller();
    MainWindow _mainWindow;
    // TODO: use it.
//    QSize _areaSize;
    Point _viewer;
//    Shape* _shape = nullptr;
    std::unique_ptr<Shape*> _shape;
    QColor _frontColor;
    QColor _backColor;
    bool _isPainted;
    int _uCount;
    int _vCount;
    // Little factory using lambds
    QMap<QString, std::unique_ptr<Shape*> (*) () > _shapes;

signals:

public slots:
    void figureChanged(QString);
    void changeViewerPos(Point);
    void moveViewer(float, float);
    void colorsChanged(QColor, QColor);
    void isPaintedChangd(bool);
    void uvChanged(int, int);
    void uvStepsChanged(int, int);
    void paramsChanged(int, int);
};

#endif // CONTROLLER_H
