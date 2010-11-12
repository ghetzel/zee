TEMPLATE = lib
MOC_DIR = moc
OBJECTS_DIR = obj
CONFIG += plugin
CONFIG += console
INCLUDEPATH += .
INCLUDEPATH += ../..
INCLUDEPATH += ../../..
INCLUDEPATH += /usr/include
DEPENDPATH += .
DEPENDPATH += ../..
DEPENDPATH += ../../..
DESTDIR = ../../../plugins
TARGET = $$qtLibraryTarget(zcm_comm)
QT += xml
QT += network
include(../../../zcm.pri)
HEADERS += zcmcommmodule.h \
    zchatclient.h \
    ztimedsource.h \
    zsocketsource.h \
    zchataccount.h
SOURCES += zcmcommmodule.cpp \
    zchatclient.cpp \
    ztimedsource.cpp \
    zsocketsource.cpp \
    zchataccount.cpp
LIBS += -lglib-2.0
LIBS += -lpurple
QMAKE_LFLAGS_PLUGIN += -Wl,--whole-archive
#linux-g++ {
    INCLUDEPATH += /usr/include/libpurple/
    INCLUDEPATH += /usr/include/glib-2.0/
    INCLUDEPATH += /usr/lib/glib-2.0/include/
    INCLUDEPATH += /usr/lib64/glib-2.0/include/
#}
