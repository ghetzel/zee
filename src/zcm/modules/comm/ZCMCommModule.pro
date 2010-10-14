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
TARGET = $$qtLibraryTarget(zcm_comm)
QT += xml
include(../../../zcm.pri)
HEADERS += zcmcommmodule.h \
    zchatclient.h
SOURCES += zcmcommmodule.cpp \
    zchatclient.cpp

LIBS += -lglib-2.0
LIBS += -lpurple

linux-g++{
    INCLUDEPATH += /usr/include/libpurple/
    INCLUDEPATH += /usr/include/glib-2.0/
    INCLUDEPATH += /usr/lib64/glib-2.0/include/
    INCLUDEPATH += /usr/lib/glib-2.0/include/
}
