#ifndef LIGHTING_H
#define LIGHTING_H

#include "point.hpp"
#include <QColor>

class Lighting
{
    Point lightPos_;
    QColor lightColor_;
    QColor polygonColor_;


public:
    Lighting();
//    QColor getPolygonColor(){return polygonColor_;}
//    void setPolygonColor(QColor&& color){ polygonColor_ = color; }
//    virtual QColor getPixelColor();
};

#endif // LIGHTING_H
