#include "polygon.h"
#include <cmath>
#include <numeric>

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
    // (x, y, z) -- normal vector
    int x = ay * bz - az * by;
    int y = az * bx - ax * bz;
    int z = ax * by - ay * bx;
    float len = sqrt(x * x + y * y + z * z);
    return (float)z / len;
}

Polygon::Polygon(Point one, Point two, Point three){
    _points[0] = one;
    _points[1] = two;
    _points[2] = three;
    _cos = computeCos();
}

int Polygon::getAverageZ(){
    int acc = 0;
    for(auto &i : _points){
        acc += i.getZ();
    }
    return acc / _countCorners;
}
