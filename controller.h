#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "mainwindow.h"
#include "point.h"
#include <QObject>
#include <QMap>
#include <QImage>
#include <functional>
#include "shape.h"
#include <vector>
#include "coloredpolygon.h"
#include <memory>

class Controller : public QObject
{
    Q_OBJECT
public:
    static Controller* instance();
    QImage *getPixmap();
    QColor getPolygonColor(Polygon&);
    std::unique_ptr<QImage*> _pixMap;
    inline bool isPainted(){return _isPainted;}
    ~Controller();
private:
    std::vector<ColoredPolygon> _plgns;
    void refreshPoints();
    void refreshPixMap();
    void refreshPolygonColors();
    void polygonOnPixmap(ColoredPolygon&);
    static Controller* _self;
    Controller();
    MainWindow _mainWindow;
    QSize _areaSize;
    Point _viewer;
    std::vector<int> _zBuffer;
    std::shared_ptr<Shape*> _shape;
    void setWindowSliders();
    QColor _frontColor;
    QColor _backColor;
    bool _isPainted;
    // Little factory using lambds
    QMap< QString, std::shared_ptr<Shape*> (*) () > _shapes;

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
    void animationStep();
};

#endif // CONTROLLER_H
