#ifndef POINT_H
#define POINT_H
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
    Point(int x, int y, int z);
    Point(matrix<int> m);
    inline int getX(){return _x;}
    inline int getY(){return _y;}
    inline int getZ(){return _z;}
    matrix<int> makeMatrix();
};

#endif // POINT_H
