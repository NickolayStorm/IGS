#include "point.h"
Point::Point(){
    _x = 0;
    _y = 0;
    _z = 0;
}

Point::Point(float x, float y, float z) : _x(x), _y(y), _z(z)
{

}

Point::Point(const Point &oth){
    _x = oth._x;
    _y = oth._y;
    _z = oth._z;
}

Point::Point(matrix<float> m){
    _x = m(0, 0);
    _y = m(0, 1);
    _z = m(0, 2);
}

matrix<float> Point::makeMatrix(){
    matrix<float> m(1, 4);
    m(0, 0) = _x;
    m(0, 1) = _y;
    m(0, 2) = _z;
    m(0, 3) = 1;
    return m;
}

float Point::distance(Point &p){
    return (this->operator -(p)).length();
}
