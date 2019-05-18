#-------------------------------------------------
#
# Project created by QtCreator 2019-03-13T01:58:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AGV_System
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    node.cpp \
    graph.cpp \
    ksp.cpp \
    mainwindow.cpp \
    widget.cpp \
    car.cpp \
    task.cpp \
    geneticalgorithm.cpp \
    taskprocessor.cpp \
    chromosome.cpp \
    timewindow.cpp \
    timewindowtable.cpp \
    timewindowsbycar.cpp \
    timewindowsbyedge.cpp \
    pointgroupmodel.cpp \
    mapmodel.cpp \
    edgegroupmodel.cpp \
    cargroupmodel.cpp

HEADERS  += \
    node.h \
    graph.h \
    ksp.h \
    mainwindow.h \
    widget.h \
    car.h \
    task.h \
    geneticalgorithm.h \
    taskprocessor.h \
    chromosome.h \
    timewindow.h \
    timewindowtable.h \
    timewindowsbycar.h \
    timewindowsbyedge.h \
    pointgroupmodel.h \
    mapmodel.h \
    edgegroupmodel.h \
    cargroupmodel.h

FORMS    += \
    mainwindow.ui \
    widget.ui

DISTFILES +=
