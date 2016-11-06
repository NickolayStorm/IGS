#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QColor inside, QColor outside, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _inside = inside;
    _outside = outside;

    updateColorWidget(ui->insideColor, _inside);
    updateColorWidget(ui->outsideColor, _outside);

    connect(ui->sliderViewerX, SIGNAL(valueChanged(int)), this, SLOT(sliderChanged()));
    connect(ui->sliderViewerY, SIGNAL(valueChanged(int)), this, SLOT(sliderChanged()));
    connect(ui->sliderViewerZ, SIGNAL(valueChanged(int)), this, SLOT(sliderChanged()));

    connect(ui->insideColorButton, SIGNAL(clicked()), this, SLOT(changeInsideColor()));
    connect(ui->outsideColorButton, SIGNAL(clicked()), this, SLOT(changeOutsideColor()));

    connect(ui->isPainted, SIGNAL(stateChanged(int)), this, SLOT(isPainted(int)));

}

void MainWindow::changeInsideColor(){
    QColor col = QColorDialog::getColor(_inside, this,
                                        QString("Choose inside color"));
    if(col.isValid()){
        _inside = col;
        updateColorWidget(ui->insideColor, col);
        emit colorsChanged(_inside, _outside);
    }
}

void MainWindow::changeOutsideColor(){
    QColor col = QColorDialog::getColor(_inside, this,
                                        QString("Choose outside color"));
    if(col.isValid()){
        _outside = col;
        updateColorWidget(ui->outsideColor, col);
        emit colorsChanged(_inside, _outside);
    }
}


void MainWindow::updateColorWidget(QWidget *w, QColor col){
    QPalette Pal(palette());

    Pal.setColor(QPalette::Background, col);
    w->setAutoFillBackground(true);
    w->setPalette(Pal);
}

void MainWindow::sliderChanged(){
    Point viewer(
              ui->sliderViewerX->value(),
              ui->sliderViewerY->value(),
              ui->sliderViewerZ->value()
          );
    emit slidersChanged(viewer);
}

void MainWindow::isPainted(int is){
    emit isPaintedChanged(is);
}

void MainWindow::updateDrawingArea(){
    ui->drawingArea->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}
