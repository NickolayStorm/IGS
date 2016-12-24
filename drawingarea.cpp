#include "drawingarea.h"
#include "drawing.h"
#include "transforms.h"
#include "point.h"
#include "controller.h"
#include <QDebug>
#define AXIS_HALF_LEN 150
DrawingArea::DrawingArea(QWidget *parent) : QWidget(parent)
{
    this->show();
}
void DrawingArea::paintEvent(QPaintEvent*){

    QPainter paint(this);
    Drawing().setColorParams(paint, Drawing::ColorOption::WhitePalette);

    Transforms transforms;
    transforms.printMatrix();

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
