#ifndef COLOREDPOLYGON_H
#define COLOREDPOLYGON_H
#include "polygon.h"
#include <QColor>

class ColoredPolygon : public Polygon
{
    QColor _color;
public:
    ColoredPolygon(Point, Point, Point, QColor = Qt::black);
    QColor getColor(){ return _color;}
    void setColor(QColor col){_color = col;}
};

#endif // COLOREDPOLYGON_H
