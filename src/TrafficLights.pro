#-------------------------------------------------
#
# Project created by QtCreator 2014-09-27T18:35:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TraficLite
TEMPLATE = app


SOURCES += main.cpp\
        uiwindow.cpp \
    road.cpp \
    roadarea.cpp \
    car.cpp

HEADERS  += uiwindow.h \
    road.h \
    roadarea.h \
    car.h

FORMS    += uiwindow.ui

CONFIG += C++11
