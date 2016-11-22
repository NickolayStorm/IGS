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
    Drawing().setColorParams(paint, Drawing::ColorOption::BlackPalette);

    Transforms transforms;
    transforms.printMatrix();

    auto *plgns = Controller::instance()->getPolygons();
    auto mapping = [&](Point p){
        return transforms.transform(p);
    };

    if(Controller::instance()->isPainted()){
        for(auto& p : *plgns){
            auto points = p.pointsToQPoint(mapping);
            auto color = Controller::instance()->getPolygonColor(p);
            Drawing().drawPolygon(paint, points.get(), p.cornerCount(), color);
        }
    }else{
        for(auto& p : *plgns){
            auto points = p.pointsToQPoint(mapping);
            Drawing().drawPolygon(paint, points.get(), p.cornerCount());
        }
    }

    // X axe
    Point startX(AXIS_HALF_LEN, 0, 0);
    Point endX(-AXIS_HALF_LEN, 0, 0);

    auto qstartX = transforms.transform(startX);
    auto qendX = transforms.transform(endX);

    Drawing().drawAxe(paint, qstartX, qendX, "X");

    // Z axe
    Point startZ(0, 0, AXIS_HALF_LEN);
    Point endZ(0, 0, -AXIS_HALF_LEN);


    auto qstartZ = transforms.transform(startZ);
    auto qendZ = transforms.transform(endZ);

    Drawing().drawAxe(paint, qstartZ, qendZ, "Z");

    // Y axe
    Point startY(0, AXIS_HALF_LEN, 0);
    Point endY(0, -AXIS_HALF_LEN, 0);

    auto qstartY = transforms.transform(startY);
    auto qendY = transforms.transform(endY);

    Drawing().drawAxe(paint, qstartY, qendY, "Y");

}
