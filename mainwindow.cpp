#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->sliderViewerX, SIGNAL(valueChanged(int)), this, SLOT(sliderChanged()));
    connect(ui->sliderViewerY, SIGNAL(valueChanged(int)), this, SLOT(sliderChanged()));
    connect(ui->sliderViewerZ, SIGNAL(valueChanged(int)), this, SLOT(sliderChanged()));

}

void MainWindow::sliderChanged(){
    Point viewer(
              ui->sliderViewerX->value(),
              ui->sliderViewerY->value(),
              ui->sliderViewerZ->value()
          );
    emit slidersChanged(viewer);
}

void MainWindow::updateDrawingArea(){
    ui->drawingArea->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}
