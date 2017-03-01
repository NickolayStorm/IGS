#include "polygon.h"
#include <cmath>
#include <numeric>

float Polygon::computeCos(){
    float len = _normal.length();
    return _normal.getZ() / len;
}

Polygon::Polygon(Point one, Point two, Point three){
    _points[0] = one;
    _points[1] = two;
    _points[2] = three;
    _normal = computeNormal();
    _cos = computeCos();
}

Polygon::Polygon(const Polygon & oth){
    _points[0] = oth._points[0];
    _points[1] = oth._points[1];
    _points[2] = oth._points[2];
    _normal = oth._normal;
    _cos = oth._cos;
}

int Polygon::getAverageZ(){
    int acc = 0;
    for(auto &i : _points){
        acc += i.getZ();
    }
    return acc / _countCorners;
}
