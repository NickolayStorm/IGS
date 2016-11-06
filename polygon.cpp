#include "polygon.h"
#include <cmath>

Polygon::Polygon(Point* points)
{
    for(int i = 0; i < _countCorners; ++i){
        _points[i] = Point(points->getX(),
                           points->getY(),
                           points->getZ());
        ++points;
    }
    _cos = computeCos();
}

float Polygon::computeCos(){
    int ax = _points[1].getX() - _points[0].getX();
    int ay = _points[1].getY() - _points[0].getY();
    int az = _points[1].getZ() - _points[0].getZ();
    int bx = _points[2].getX() - _points[0].getX();
    int by = _points[2].getY() - _points[0].getY();
    int bz = _points[2].getZ() - _points[0].getZ();
    int x = ay * bz - az * by;
    int y = az * bx - ax * bz;
    int z = ax * by - ay * bx;
    float size = sqrt(x * x + y * y + z * z);
    return (float)z / size;
}

Polygon::Polygon(Point one, Point two, Point three){
    _points[0] = one;
    _points[1] = two;
    _points[2] = three;
    _cos = computeCos();
}

std::unique_ptr< QPoint[] >
Polygon::pointsToQPoint(std::function< QPoint (Point) > mapping){
    auto smartptr = std::make_unique< QPoint[] >(_countCorners);
    for(int i = 0; i < _countCorners; ++i){
        smartptr[i] = mapping(_points[i]);
    }
    return std::move(smartptr);
}
