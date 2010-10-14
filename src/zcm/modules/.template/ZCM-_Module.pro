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
TARGET = $$qtLibraryTarget(zcm_%MODULENAME%)
QT += xml
include(../../../zcm.pri)
HEADERS += zcm%MODULENAME%module.h
SOURCES += zcm%MODULENAME%module.cpp

