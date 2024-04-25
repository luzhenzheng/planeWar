#-------------------------------------------------
#
# Project created by QtCreator 2024-03-04T17:58:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = planeWar
TEMPLATE = app


SOURCES += main.cpp\
    map.cpp \
    heroplane.cpp \
    mainscene.cpp \
    bullet.cpp \
    enemyplane.cpp \
    bomb.cpp

HEADERS  += \
    config.h \
    map.h \
    heroplane.h \
    mainscene.h \
    bullet.h \
    enemyplane.h \
    bomb.h

RESOURCES += \
    res.qrc
CONFIG+=resources_big
