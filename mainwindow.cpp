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

    // U-V
    connect(ui->sliderU, SIGNAL(valueChanged(int)), this, SLOT(changeUV()));
    connect(ui->sliderV, SIGNAL(valueChanged(int)), this, SLOT(changeUV()));

    // Steps
    connect(ui->sliderUStep, SIGNAL(valueChanged(int)), this, SLOT(changeUVSteps()));
    connect(ui->sliderVStep, SIGNAL(valueChanged(int)), this, SLOT(changeUVSteps()));

    // Figure params
    connect(ui->sliderParam1, SIGNAL(valueChanged(int)), this, SLOT(changeParams()));
    connect(ui->sliderParam2, SIGNAL(valueChanged(int)), this, SLOT(changeParams()));

    // Figure choose
    connect(ui->comboBoxFigure, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(changeFigure(QString)));

    // Colors
    connect(ui->insideColorButton, SIGNAL(clicked()), this, SLOT(changeInsideColor()));
    connect(ui->outsideColorButton, SIGNAL(clicked()), this, SLOT(changeOutsideColor()));

    // Check boxes
    connect(ui->isPainted, SIGNAL(stateChanged(int)), this, SLOT(isPainted(int)));

    // Move viewer position on mouse
    connect(ui->drawingArea, SIGNAL(moveViewerPos(QPoint)), this, SLOT(moveViewerPos(QPoint)));

}

void MainWindow::enableAll(bool is){
    ui->sliderParam1->setEnabled(is);
    ui->sliderParam2->setEnabled(is);
    ui->sliderU->setEnabled(is);
    ui->sliderV->setEnabled(is);
    ui->sliderUStep->setEnabled(is);
    ui->sliderVStep->setEnabled(is);
    ui->comboBoxFigure->setEnabled(is);
}

void MainWindow::changeUV(){
    emit uvChanged(ui->sliderU->value(),
                   ui->sliderV->value());
}

void MainWindow::changeUVSteps(){
    emit uvStepsChanged(ui->sliderUStep->value(),
                        ui->sliderVStep->value());
}

void MainWindow::changeParams(){
    emit paramsChanged(ui->sliderParam1->value(),
                       ui->sliderParam2->value());
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
    QColor col = QColorDialog::getColor(_outside, this,
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

void MainWindow::changeFigure(QString name){
    emit figureChanged(name);
}

void MainWindow::isPainted(int is){
    emit isPaintedChanged(is);
}

void MainWindow::updateDrawingArea(){
    ui->drawingArea->update();
}

void
MainWindow::setUVSliderParams(int umax, int vmax, int ucurr, int vcurr){
    ui->sliderU->setMaximum(umax);
    ui->sliderV->setMaximum(vmax);
    ui->sliderU->setValue(ucurr);
    ui->sliderV->setValue(vcurr);
}

void MainWindow::setFigureSliderParams(int fst, int snd){
    ui->sliderParam1->setValue(fst);
    ui->sliderParam2->setValue(snd);
}

void MainWindow::setShapeNames(QStringList& names){
    ui->comboBoxFigure->clear();
    ui->comboBoxFigure->insertItems(0, names);
}

void MainWindow::moveViewerPos(QPoint diff){
    float x = (float)diff.x() / 90.0;
    float y = (float)diff.y() / 90.0;
    emit viewerPosMoved(x, y);
}

QSize MainWindow::drawingAreaSize(){
    return ui->drawingArea->size();
}

MainWindow::~MainWindow()
{
    delete ui;
}
