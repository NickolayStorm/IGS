#ifndef POLYGON_H
#define POLYGON_H
#include <point.h>
#include <functional>
#include <memory>
#include <QPoint>
class Polygon
{
    static const short _countCorners = 3;
    Point _points[_countCorners];
    float computeCos();
    float _cos;
public:
    Polygon(Point*);
    Polygon(Point, Point, Point);
    static constexpr short cornerCount(){
        return _countCorners;
    }
    inline float getCos(){return _cos;}
    std::unique_ptr < QPoint[] >
    pointsToQPoint(std::function<QPoint (Point)> mapping);
};

#endif // POLYGON_H
