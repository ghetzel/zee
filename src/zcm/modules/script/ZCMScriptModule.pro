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
HEADERS += zcmscriptmodule.h \
    zrubyscript.h
SOURCES += zcmscriptmodule.cpp \
    zrubyscript.cpp
linux-g++:INCLUDEPATH += /usr/include
linux-g++:INCLUDEPATH += /usr/lib64/ruby/1.8/x86_64-linux/

LIBS += -lruby
