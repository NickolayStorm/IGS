#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include "point.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QColor inside, QColor outside, QWidget *parent = 0);
    void updateDrawingArea();
    ~MainWindow();
signals:
    void slidersChanged(Point);
    void colorsChanged(QColor, QColor);
    void isPaintedChanged(bool);
public slots:
    void isPainted(int);
    void sliderChanged();
    void changeInsideColor();
    void changeOutsideColor();
private:
    Ui::MainWindow *ui;
    QColor _inside;
    QColor _outside;
    void updateColorWidget(QWidget *, QColor);
};

#endif // MAINWINDOW_H
