QT += core
QT -= gui

TARGET = clude
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

include(clude.pri)

DISTFILES += \
    cludepackage.json
