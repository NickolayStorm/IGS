#ifndef TRANSFORMS_H
#define TRANSFORMS_H
#include "point.h"
#include <QPoint>
using namespace boost::numeric::ublas;
class Transforms
{
public:
//    Transforms();
//static Transforms* _self = nullptr;
    static QPoint transform(Point point, Point viewer, int center);
    static matrix<float> transfer(QPoint);
    static matrix<float> rotationX(Point viewer);
    //static Point rotationY(float fi){}
    static matrix<float> rotationZ(Point viewer);
    static matrix<float> projaction();
    static inline matrix<float> mirror_yoz();
    static matrix<float> identityMatrix();



};

#endif // TRANSFORMS_H
