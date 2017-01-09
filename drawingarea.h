#ifndef DRAWINGAREA_H
#define DRAWINGAREA_H
#include <QWidget>


class DrawingArea : public QWidget
{
    Q_OBJECT
    QPoint _prevCursorPos;
public:
    explicit DrawingArea(QWidget *parent = 0);
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

signals:
    void moveViewerPos(QPoint);

public slots:
};

#endif // DRAWINGAREA_H
