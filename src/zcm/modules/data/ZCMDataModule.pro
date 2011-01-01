TEMPLATE = lib
MOC_DIR = moc
OBJECTS_DIR = obj
CONFIG += plugin
CONFIG += console
INCLUDEPATH += .
INCLUDEPATH += ../..
INCLUDEPATH += ../../..
linux-g++:INCLUDEPATH += /usr/include
DEPENDPATH += .
DEPENDPATH += ../..
DEPENDPATH += ../../..
DESTDIR = ../../../plugins
TARGET = $$qtLibraryTarget(zcm_data)
QT += xml
QT += sql
include(../../../zcm.pri)
HEADERS += zcmdatamodule.h \
    zdatamodel.h \
    zdatabase.h
SOURCES += zcmdatamodule.cpp \
    zdatamodel.cpp \
    zdatabase.cpp
