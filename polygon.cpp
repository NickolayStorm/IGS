#include "polygon.h"

Polygon::Polygon(Point* points)
{
    for(int i = 0; i < _countCorners; ++i){
        _points[i] = Point(points->getX(),
                           points->getY(),
                           points->getZ());
        ++points;
    }

}

Polygon::Polygon(Point one, Point two, Point three){
    _points[0] = one;
    _points[1] = two;
    _points[2] = three;
//    _points[3] = four;
}

std::unique_ptr< QPoint[] >
Polygon::pointsToQPoint(std::function<QPoint (Point)> mapping){
    auto smartptr = std::make_unique<QPoint[]>(_countCorners);
    for(int i = 0; i < _countCorners; ++i){
        smartptr[i] = mapping(_points[i]);
    }
    return std::move(smartptr);
}
