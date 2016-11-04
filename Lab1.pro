#-------------------------------------------------
#
# Project created by QtCreator 2016-10-01T12:24:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lab1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    drawingarea.cpp \
    drawing.cpp \
    transforms.cpp \
    point.cpp \
    controller.cpp

HEADERS  += mainwindow.h \
    drawingarea.h \
    drawing.h \
    transforms.h \
    point.h \
    controller.h

FORMS    += mainwindow.ui
