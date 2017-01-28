#ifndef SHAPE_H
#define SHAPE_H
#include <QString>
#include <QMap>
#include <functional>
#include "point.h"
#include "coloredpolygon.h"

class Shape
{
protected:
    unsigned vCount, uCount;
    int _a, _b, _c;
    int uMin, uMax, vMin, vMax, uInitMax, vInitMax;
    const int DEFAULT_PARAMETR_VALUE = 50;
    const int DEFAULT_COUNT = 20;
    const int DEFAULT_MAX = 100;
    QString name;
    Point pointOn(int i, int j);
    std::vector<std::vector<Point>> makePoints(std::function<Point (Point)> mapping);
    double u, v, x, y, z;
public:
    Shape();
    std::vector<ColoredPolygon> getPolygons(std::function<Point (Point)> mapping);
    void setUV(int, int);
    QPair <int, int> getUVMax();
    QPair <int, int> getInit();
    void setStepCounts(unsigned, unsigned);
    void setParams(int fst, int snd);
    QPair <int, int> getParams();
    QPair <int, int> getUVCounts();
    virtual void func() = 0;
    virtual ~Shape();

};

#endif // SHAPE_H
