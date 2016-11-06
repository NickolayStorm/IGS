#ifndef SHAPE_H
#define SHAPE_H
#include <QString>
#include "point.h"

class Shape
{
protected:
    int vCount, uCount;
    double a, b, c;
    double uMin, uMax, vMin, vMax, uInitMax, vInitMax;
    const int DEFAULT_PARAMETR_VALUE = 50;
    const int DEFAULT_COUNT = 20;
    const int DEFAULT_MAX = 100;
    QString name;
    double u, v, x, y, z;
public:
    Shape();
    Point pointOn(int i, int j);
    virtual void func() = 0;
    virtual ~Shape();

};

#endif // SHAPE_H
