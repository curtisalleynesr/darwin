
include(../common.pri)

QT += core gui charts widgets

TARGET = core_ui
TEMPLATE = lib
CONFIG += staticlib

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    properties_widget.cpp \
    box2d_renderer.cpp \
    canvas.cpp

HEADERS += \
    properties_widget.h \
    box2d_renderer.h \
    canvas.h

addLibrary(../core)
