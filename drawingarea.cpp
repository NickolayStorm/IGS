#include "drawingarea.h"
#include "drawing.h"
#include "transforms.h"
#include "point.h"
#include "controller.h"
#include <QMouseEvent>
#include <QDebug>
#define AXIS_HALF_LEN 150
DrawingArea::DrawingArea(QWidget *parent) : QWidget(parent)
{
    this->show();
}

void DrawingArea::mousePressEvent(QMouseEvent *event){
    _prevCursorPos = event->pos();
}

void DrawingArea::mouseMoveEvent(QMouseEvent *event){
    QPoint diff = _prevCursorPos - event->pos();
    _prevCursorPos = event->pos();
    emit moveViewerPos(diff);
}

void DrawingArea::paintEvent(QPaintEvent*){

    QPainter paint(this);
    Drawing().setColorParams(paint, Drawing::ColorOption::WhitePalette);

    auto *plgns = Controller::instance()->getPolygons();

    if(Controller::instance()->isPainted()){
        for(auto& p : *plgns){
            auto color = Controller::instance()->getPolygonColor(p);
            auto points = p.getPoints();
            std::array<QPoint, 3> qpoints;
            std::transform(points.begin(), points.end(),
                           qpoints.begin(),
                           [](auto &x){ return x.getQPoint();}
            );
            Drawing().drawPolygon(paint, qpoints.data(), p.cornerCount(), color);
        }
    }
    else{
        for(auto& p : *plgns){
            auto points = p.getPoints();
            std::array<QPoint, 3> qpoints;
            std::transform(points.begin(), points.end(),
                           qpoints.begin(),
                           [](auto &x){ return x.getQPoint();}
            );
            Drawing().drawPolygon(paint, qpoints.data(), p.cornerCount());
        }
    }
}
