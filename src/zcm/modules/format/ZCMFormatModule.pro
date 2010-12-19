TEMPLATE = lib
MOC_DIR = moc
OBJECTS_DIR = obj
CONFIG += plugin
CONFIG += console
INCLUDEPATH += .
INCLUDEPATH += ../..
INCLUDEPATH += ../../..
DEPENDPATH += .
DEPENDPATH += ../..
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
    zunitformatter.h \
    znumberformatter.h \
    zformatterinterface.h \
    zregexformatter.h
SOURCES += zcmformatmodule.cpp \
    zformatter.cpp \
    zstringformatter.cpp \
    zdateformatter.cpp \
    ztransformation.cpp \
    zunitformatter.cpp \
    znumberformatter.cpp \
    zregexformatter.cpp \
    zabstractformatter.cpp
LIBS += -ludunits2
linux-g++:INCLUDEPATH += /usr/include
