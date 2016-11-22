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
    void setUVSliderParams(int umax, int vmax, int ucurr, int vcurr);
    void setFigureSliderParams(int fst, int snd);
    void setShapeNames(QStringList& names);
    ~MainWindow();
signals:
    void slidersChanged(Point);
    void colorsChanged(QColor, QColor);
    void isPaintedChanged(bool);
    void uvChanged(int, int);
    void uvStepsChanged(int, int);
    void paramsChanged(int, int);
    void figureChanged(QString);
public slots:
    void isPainted(int);
    void sliderChanged();
    void changeInsideColor();
    void changeOutsideColor();
    void changeUV();
    void changeParams();
    void changeUVSteps();
    void changeFigure(QString);
private:
    Ui::MainWindow *ui;
    QColor _inside;
    QColor _outside;
    void updateColorWidget(QWidget *, QColor);
};

#endif // MAINWINDOW_H
