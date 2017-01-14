#ifndef POINT_H
#define POINT_H
#include <QPoint>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
using namespace boost::numeric::ublas;

class Point
{
private:
    int _x;
    int _y;
    int _z;
public:
    Point();
    Point(int x, int y, int z);
    Point(matrix<int> m);
    Point(const Point&);
    inline int getX(){return _x;}
    inline void setX(int x){_x = x;}
    inline int getY(){return _y;}
    inline int getZ(){return _z;}
    matrix<int> makeMatrix();
    inline QPoint getQPoint(){return QPoint(_x, _y);}

    Point operator + (const Point &v) const { Point p(_x+v._x, _y+v._y, _z+v._z); return p; }
    Point operator - (const Point &v) const { Point p(_x-v._x, _y-v._y, _z-v._z); return p; }
    Point operator * (float f)        const { Point p(_x*f, _y*f, _z*f);          return p; }
};

#endif // POINT_H
