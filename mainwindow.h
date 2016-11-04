#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "point.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void updateDrawingArea();
    ~MainWindow();
signals:
    void slidersChanged(Point);
public slots:
    void sliderChanged();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
