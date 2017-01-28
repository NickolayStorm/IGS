#ifndef POINT_H
#define POINT_H
#include <QPoint>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
using namespace boost::numeric::ublas;

class Point
{
private:
    float _x;
    float _y;
    float _z;
public:
    Point();
    Point(float x, float y, float z);
    Point(matrix<float> m);
    Point(const Point&);
    inline int getX(){return _x;}
    inline void setX(int x){_x = x;}
    inline int getY(){return _y;}
    inline int getZ(){return _z;}
    matrix<float> makeMatrix();
    inline QPoint getQPoint(){return QPoint(_x, _y);}
    inline float length(){ return sqrt((_x*_x) + (_y*_y) + (_z*_z)); }
    float distance(Point& p);
    Point operator + (const Point &v) const { Point p(_x+v._x, _y+v._y, _z+v._z); return p; }
    Point operator - (const Point &v) const { Point p(_x-v._x, _y-v._y, _z-v._z); return p; }
    Point operator * (float f)        const { Point p(_x*f, _y*f, _z*f);          return p; }
    Point operator / (float f)        const { Point p(_x/f, _y/f, _z/f);          return p; }
};

#endif // POINT_H
