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

HEADERS +=  zcmscriptmodule.h   \
            zrubyscript.h       \
            zabstractscript.h

SOURCES +=  zcmscriptmodule.cpp \
            zrubyscript.cpp     \
            zabstractscript.cpp

INCLUDEPATH += /usr/include
INCLUDEPATH += /usr/include/ruby-1.9.1/
INCLUDEPATH += /usr/lib/ruby/1.8/i386-linux/
INCLUDEPATH += /usr/lib64/ruby/1.8/x86_64-linux/

LIBS += -lruby
