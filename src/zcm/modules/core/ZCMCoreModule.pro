TEMPLATE = lib
MOC_DIR = moc
OBJECTS_DIR = obj
CONFIG += plugin
CONFIG += console
INCLUDEPATH += .
INCLUDEPATH += ../../..
DEPENDPATH += .
DEPENDPATH += ../../..
HEADERS += zcmcoremodule.h \
    libzee/zlocalsystem.h \
    zcm/zcmplugin.h \
    zcm/zcmplugininterface.h \
    zutil.h \
    zplugininterface.h \
    zeventmanager.h \
    zeventrelationship.h \
    zsetting.h \
    zmethodobject.h \
    zeventobject.h \
    ztimer.h \
    zsysteminfo.h
SOURCES += zcmcoremodule.cpp \
    libzee/zlocalsystem.cpp \
    zutil.cpp \
    zeventmanager.cpp \
    zeventrelationship.cpp \
    zsetting.cpp \
    zmethodobject.cpp \
    zeventobject.cpp \
    ztimer.cpp \
    zsysteminfo.cpp
DESTDIR = ../../../plugins
TARGET = $$qtLibraryTarget(zcm_core)
QT += xml
