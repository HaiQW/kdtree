TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    kdtree.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    kdtree.h

