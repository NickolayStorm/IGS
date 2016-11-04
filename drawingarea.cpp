#include "drawingarea.h"
#include "drawing.h"
#include "transforms.h"
#include "point.h"
#include "controller.h"
#include <QDebug>
#define AXIS_HALF_LEN 100
DrawingArea::DrawingArea(QWidget *parent) : QWidget(parent)
{
    this->show();
}
void DrawingArea::paintEvent(QPaintEvent*){

    Point viewer = Controller::instance()->getViewer();

    qDebug() << "viewer: ("
             << viewer.getX() << " "
             << viewer.getY() << " "
             << viewer.getZ() << endl;

    QPainter paint(this);
    Drawing().setColorParams(paint, Drawing::ColorOption::BlackPalette);


    Point point(0,0,0);
    int center = this->size().width()/2;
    QPoint drawingPoint = Transforms::transform(point, viewer, center);

    // X axe
    Point startX(AXIS_HALF_LEN, 0, 0);
    Point endX(-AXIS_HALF_LEN, 0, 0);

    auto qstartX = Transforms::transform(startX, viewer, center);
    auto qendX = Transforms::transform(endX, viewer, center);

    Drawing().drawPoint(paint, drawingPoint);
    Drawing().drawAxe(paint, qstartX, qendX, "X");
//    qDebug() << qstartX << " " << qendX;

    // Z axe
    qDebug() << "### Z AXE ###";
    Point startZ(0, 0, AXIS_HALF_LEN);
    Point endZ(0, 0, -AXIS_HALF_LEN);


    auto qstartZ = Transforms::transform(startZ, viewer, center);
    auto qendZ = Transforms::transform(endZ, viewer, center);

    Drawing().drawPoint(paint, drawingPoint);
    Drawing().drawAxe(paint, qstartZ, qendZ, "Z");
//    qDebug() << qstartZ << " " << qendZ;

    // Y axe
    Point startY(0, AXIS_HALF_LEN, 0);
    Point endY(0, -AXIS_HALF_LEN, 0);
//    Point startY(-AXIS_HALF_LEN/2, AXIS_HALF_LEN/2, 0);
//    Point endY(AXIS_HALF_LEN/2, -AXIS_HALF_LEN/2, 0);

    auto qstartY = Transforms::transform(startY, viewer, center);
    auto qendY = Transforms::transform(endY, viewer, center);

    Drawing().drawPoint(paint, drawingPoint);
    Drawing().drawAxe(paint, qstartY, qendY, "Y");
//    qDebug() << qstartZ << " " << qendZ;

}
