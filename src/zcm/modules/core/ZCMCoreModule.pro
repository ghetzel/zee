TEMPLATE = lib
MOC_DIR = moc
OBJECTS_DIR = obj
CONFIG += plugin
CONFIG += console
INCLUDEPATH += .
INCLUDEPATH += ../../..

DEPENDPATH += .
DEPENDPATH += ../../..

include(../../../zcm.pri)

HEADERS +=  zcmcoremodule.h \
            libzee/zlocalsystem.h \
            zsetting.h \
            ztimer.h \
            zsysteminfo.h \
            zexecutor.h \
            zsqlquery.h \
            zshortcut.h \
            zlinuxauthenticator.h

SOURCES +=  zcmcoremodule.cpp \
            libzee/zlocalsystem.cpp \
            zsetting.cpp \
            ztimer.cpp \
            zsysteminfo.cpp \
            zexecutor.cpp \
            zsqlquery.cpp \
            zshortcut.cpp \
            zlinuxauthenticator.cpp

DESTDIR = ../../../plugins
TARGET = $$qtLibraryTarget(zcm_core)
QT += xml \
    sql
linux-g++ {
    QT += dbus
    LIBS += -lpam -lpam_misc
    HEADERS += zdbusinterface.h
    SOURCES += zdbusinterface.cpp
}
