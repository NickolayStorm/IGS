#ifndef POLYGON_H
#define POLYGON_H
#include <point.hpp>
#include <functional>
#include <memory>
#include <QPoint>
#include <array>
class Polygon
{
    static const short _countCorners = 3;
    std::array<Point, 3> _points;
    inline Point computeNormal(){
        float ax = _points[1].getX() - _points[0].getX();
        float ay = _points[1].getY() - _points[0].getY();
        float az = _points[1].getZ() - _points[0].getZ();
        float bx = _points[2].getX() - _points[0].getX();
        float by = _points[2].getY() - _points[0].getY();
        float bz = _points[2].getZ() - _points[0].getZ();
        // (x, y, z) -- normal vector
        float x = ay * bz - az * by;
        float y = az * bx - ax * bz;
        float z = ax * by - ay * bx;
        return std::move(Point(x, y, z));
    }

    float computeCos();
    float _cos;
    Point _normal;
public:
    Polygon(Point, Point, Point);
    Polygon(const Polygon&);
    static constexpr short cornerCount(){
        return _countCorners;
    }
    inline Point getNormal(){return _normal;}
    inline float getCos(){return _cos;}
    inline std::array<Point, 3> getPoints(){return _points;}
    int getAverageZ();
};

#endif // POLYGON_H
