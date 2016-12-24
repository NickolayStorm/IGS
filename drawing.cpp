#include "drawing.h"
#include <QPen>
//Drawing* Drawing::_self = nullptr;
Drawing::Drawing()
{

}

//Drawing* Drawing::instance(){
//    if(Drawing::_self == nullptr)
//        Drawing::_self = new Drawing();
//    return Drawing::_self;

//}

void Drawing::drawPoint(QPainter& paint, QPoint& point){
    paint.drawEllipse(point, 3, 3);
}

void Drawing::drawAxe(QPainter &paint, QPoint &begin, QPoint &end, QString name){
    paint.drawLine(begin, end);
    paint.drawText(begin - QPoint(5, 5), name);
}

void Drawing::setColorParams(QPainter &paint, ColorOption opts){
    QPen pen;
    if(opts & ColorOption::WhitePalette){
        pen.setColor(Qt::white);
    }else{
        pen.setColor(Qt::black);
    }
    paint.setPen(pen);
}

void Drawing::drawPolygon(QPainter &paint, QPoint *points, int size){
    paint.drawPolygon(points, size);
}

void Drawing::drawPolygon(QPainter &paint, QPoint *points, int size, QColor color){
    QBrush brush;
    brush.setColor(color);
    brush.setStyle(Qt::SolidPattern);
    paint.setBrush(brush);
    QPen pen;
    pen.setColor(color);
    paint.setPen(pen);

    paint.drawPolygon(points, size);
}
