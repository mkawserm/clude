QT += core
QT -= gui

TARGET = clude
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    cludeobject.cpp \
    cludepackage.cpp \
    cludepackagedependency.cpp

HEADERS += \
    cludeobject.hpp \
    cludepackage.hpp \
    cludepackagedependency.hpp
