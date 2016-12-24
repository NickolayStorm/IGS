#ifndef SHAPE_H
#define SHAPE_H
#include <QString>
#include <QMap>
#include "point.h"

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
    double u, v, x, y, z;
public:
    Shape();
    Point pointOn(int i, int j);
    void setUV(int, int);
    QPair <int, int> getUVMax();
    QPair <int, int> getInit();
    void setStepCounts(unsigned, unsigned);
    void setParams(int fst, int snd);
    QPair <int, int> getParams();
    virtual void func() = 0;
    virtual ~Shape();

};

#endif // SHAPE_H
