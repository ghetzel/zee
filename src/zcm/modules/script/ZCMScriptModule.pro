TEMPLATE = lib
MOC_DIR = moc
OBJECTS_DIR = obj
CONFIG += plugin
CONFIG += console
INCLUDEPATH += .
INCLUDEPATH += ../../..
DEPENDPATH += .
DEPENDPATH += ../../..
DESTDIR = ../../../plugins
TARGET = $$qtLibraryTarget(zcm_script)
QT += xml
include(../../../zcm.pri)

HEADERS += zcmscriptmodule.h
SOURCES += zcmscriptmodule.cpp

linux-g++{
    INCLUDEPATH += /usr/include
}
