#include "coloredpolygon.h"

ColoredPolygon::ColoredPolygon(Point a, Point b, Point c, QColor col) :
                                Polygon(a, b, c),
                                _color(col)
{

}
