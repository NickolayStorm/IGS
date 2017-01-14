#ifndef POLYGON_H
#define POLYGON_H
#include <point.h>
#include <functional>
#include <memory>
#include <QPoint>
#include <array>
class Polygon
{
    static const short _countCorners = 3;
    std::array<Point, 3> _points;
    float computeCos();
    float _cos;
public:
    Polygon(Point*);
    Polygon(Point, Point, Point);
    Polygon(const Polygon&);
    static constexpr short cornerCount(){
        return _countCorners;
    }
    inline float getCos(){return _cos;}
    inline std::array<Point, 3> getPoints(){return _points;}
    int getAverageZ();
};

#endif // POLYGON_H
