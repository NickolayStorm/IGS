#ifndef SHAPE_H
#define SHAPE_H
#include <utility>
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
    Point pointOn(int i, int j);
    double u, v, x, y, z;
public:
    Shape();
    std::vector<ColoredPolygon> getPolygons(std::function<Point (const Point&)> mapping);

    virtual std::vector<Point>
    makePoints(std::function<Point (const Point&)> mapping);

    void setUV(int, int);
    std::pair <int, int> getUVMax() const;
    std::pair <int, int> getInit() const;
    void setStepCounts(unsigned, unsigned);
    void setParams(int fst, int snd);
    std::pair <int, int> getParams() const;
    std::pair <int, int> getUVCounts() const;
    virtual void func() = 0;
    virtual ~Shape();

};

#endif // SHAPE_H
