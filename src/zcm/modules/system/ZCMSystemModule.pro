TEMPLATE = lib
MOC_DIR = moc
OBJECTS_DIR = obj
CONFIG += plugin
CONFIG += console
INCLUDEPATH += .
INCLUDEPATH += ../../..
INCLUDEPATH += ../../../libzee/
INCLUDEPATH += /usr/local/include/
DEPENDPATH += .
DEPENDPATH += ../../..
include(../../../zcm.pri)
LIBS += -lsigar
QT += xml
HEADERS += zprocessorinfo.h \
    znetworkinfo.h \
    znetinterfaceinfo.h \
    zmemoryinfo.h \
    zhardwareinfo.h \
    zdiskinfo.h \
    zcpuinfo.h \
    zcmsystemmodule.h \
    zsysteminfo.h
SOURCES += zprocessorinfo.cpp \
    znetworkinfo.cpp \
    znetinterfaceinfo.cpp \
    zmemoryinfo.cpp \
    zhardwareinfo.cpp \
    zdiskinfo.cpp \
    zcpuinfo.cpp \
    zcmsystemmodule.cpp \
    zsysteminfo.cpp
DESTDIR = ../../../plugins
TARGET = $$qtLibraryTarget(zcm_core)
