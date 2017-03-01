#ifndef POINT_H
#define POINT_H
#include <QPoint>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
using boost::numeric::ublas::matrix;

template<typename T>
class Point_t
{
private:
    T _x;
    T _y;
    T _z;

public:

    Point_t()
    {
        _x = 0;
        _y = 0;
        _z = 0;
    }

    Point_t(T x, T y, T z)
    {
        _x = x;
        _y = y;
        _z = z;
    }

    Point_t(const Point_t& oth)
    {
        _x = oth._x;
        _y = oth._y;
        _z = oth._z;
    }

    Point_t(matrix<T> m)
    {
        _x = m(0, 0);
        _y = m(0, 1);
        _z = m(0, 2);
    }

    inline int getX(){ return _x; }
    inline int getY(){ return _y; }
    inline int getZ(){ return _z; }

    // Vector length
    inline T length(){ return sqrt((_x*_x) + (_y*_y) + (_z*_z)); }
    // Distance between two points
    T distance(Point_t<T>& p){ return (this->operator -(p)).length(); }
    inline QPoint getQPoint(){return QPoint(_x, _y);}

    matrix<T> makeMatrix(){
        matrix<T> m(1, 4);
        m(0, 0) = _x;
        m(0, 1) = _y;
        m(0, 2) = _z;
        m(0, 3) = 1;
        return m;
    }

    T getCos(Point_t<T> oth){
        return (this->operator *(oth)) / (this->length() * oth.length());
    }

    Point_t<T> operator + (const Point_t<T> &v) const { Point_t <T> p(_x+v._x, _y+v._y, _z+v._z); return p;   }
    Point_t<T> operator - (const Point_t<T> &v) const { Point_t <T> p(_x-v._x, _y-v._y, _z-v._z); return p;   }
    Point_t<T> operator * (float f)             const { Point_t <T> p(_x*f, _y*f, _z*f);          return p;   }
    Point_t<T> operator / (float f)             const { Point_t <T> p(_x/f, _y/f, _z/f);          return p;   }
    T          operator * (const Point_t<T> &v) const { T res = _x*v._x + _y*v._y + _z*v._z;      return res; }

};

typedef Point_t<float> Point;

#endif // POINT_H
