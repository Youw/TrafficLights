#-------------------------------------------------
#
# Project created by QtCreator 2014-09-27T18:35:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TraficLite
TEMPLATE = app

INCLUDEPATH += $$PWD/../include
LIBS += -L$$PWD/../lib -lfuzzylite.dll

SOURCES += main.cpp\
        uiwindow.cpp \
    road.cpp \
    car.cpp \
    crossroad.cpp \
    crossroadpainter.cpp \
    trafficlight.cpp

HEADERS  += uiwindow.h \
    road.h \
    car.h \
    crossroad.h \
    crossroadpainter.h \
    loader.h \
    trafficlight.h

FORMS    += uiwindow.ui

CONFIG += C++11
