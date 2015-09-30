QT += core
QT -= gui

TARGET = clude
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    cpackage.cpp \
    cpackagedependency.cpp \
    cludeobject.cpp

HEADERS += \
    cpackage.hpp \
    cpackagedependency.hpp \
    cludeobject.hpp
