#ifndef DRAWINGAREA_H
#define DRAWINGAREA_H
#include <QWidget>


class DrawingArea : public QWidget
{
    Q_OBJECT
public:
    explicit DrawingArea(QWidget *parent = 0);
    void paintEvent(QPaintEvent*);

signals:

public slots:
};

#endif // DRAWINGAREA_H
