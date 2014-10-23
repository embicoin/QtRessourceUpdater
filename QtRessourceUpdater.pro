#-------------------------------------------------
#
# Project created by QtCreator 2014-10-22T20:38:29
#
#-------------------------------------------------

QT       += core gui svg

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtRessourceUpdater
TEMPLATE = app


SOURCES += main.cpp\
        Window.cpp

HEADERS  += Window.hpp

FORMS    += Window.ui

OTHER_FILES +=

RESOURCES += \
    ressources.qrc
