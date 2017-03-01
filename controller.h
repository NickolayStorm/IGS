#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "mainwindow.h"
#include "point.hpp"
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
    ~Controller();

private:

    static Controller* _self;
    Controller();

    void refreshPoints();
    void refreshPixMap();
    void refreshPolygonColors();
    QColor getPolygonColor(Polygon&);
    void polygonOnPixmap(ColoredPolygon&);

    MainWindow _mainWindow;
    QSize _areaSize;
    Point _viewer;
    void setWindowSliders();

    std::unique_ptr<QImage*> _pixMap;
    std::shared_ptr<Shape*> _shape;
    std::vector<int> _zBuffer;
    std::vector<ColoredPolygon> _plgns;

    QColor _frontColor;
    QColor _backColor;
    Point _lightPos;
    QColor _lightColor;

    // Little factory using lambds
    QMap< QString, std::shared_ptr<Shape*> (*) () > _shapes;

public slots:
    void figureChanged(QString);
    void changeLightPos(int, int, int);
    void moveViewer(float, float);
    void colorsChanged(QColor, QColor);
    void uvChanged(int, int);
    void uvStepsChanged(int, int);
    void paramsChanged(int, int);
    void animationStep();
};

#endif // CONTROLLER_H
