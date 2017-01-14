#-------------------------------------------------
#
# Project created by QtCreator 2016-10-01T12:24:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = torable
TEMPLATE = app

CONFIG += C++17

SOURCES += main.cpp\
        mainwindow.cpp \
    drawingarea.cpp \
    drawing.cpp \
    transforms.cpp \
    point.cpp \
    controller.cpp \
    shape.cpp \
    tor.cpp \
    polygon.cpp \
    heart.cpp \
    toruscurve.cpp \
    ennepersurface.cpp \
    coloredpolygon.cpp

HEADERS  += mainwindow.h \
    drawingarea.h \
    drawing.h \
    transforms.h \
    point.h \
    controller.h \
    shape.h \
    tor.h \
    polygon.h \
    heart.h \
    toruscurve.h \
    ennepersurface.h \
    coloredpolygon.h

FORMS    += mainwindow.ui
