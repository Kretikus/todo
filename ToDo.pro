#-------------------------------------------------
#
# Project created by QtCreator 2014-07-01T20:39:02
#
#-------------------------------------------------

QT       += core gui widgets network

CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ToDo
TEMPLATE = app


SOURCES += main.cpp\
        todoeditor.cpp

HEADERS  += todoeditor.h

FORMS    += todoeditor.ui

RESOURCES += \
    ressources.qrc
