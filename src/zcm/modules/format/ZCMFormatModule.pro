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
TARGET = $$qtLibraryTarget(zcm_format)
QT += xml
include(../../../zcm.pri)
HEADERS += zcmformatmodule.h \
    zformatter.h \
    zabstractformatter.h \
    zstringformatter.h \
    zdateformatter.h \
    ztransformation.h \
    zunitformatter.h
SOURCES += zcmformatmodule.cpp \
    zformatter.cpp \
    zstringformatter.cpp \
    zdateformatter.cpp \
    ztransformation.cpp \
    zunitformatter.cpp

LIBS += -ludunits2 -lzee

linux-g++{
    INCLUDEPATH += /usr/include
}
