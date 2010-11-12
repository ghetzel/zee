TEMPLATE = lib
MOC_DIR = moc
OBJECTS_DIR = obj
CONFIG += plugin
CONFIG += console
INCLUDEPATH += .
INCLUDEPATH += ../../..
INCLUDEPATH += /usr/local/include/
DEPENDPATH += .
DEPENDPATH += ../../..
include(../../../zcm.pri)
HEADERS += zcmcoremodule.h \
    zsetting.h \
    ztimer.h \
    zsysteminfo.h \
    zexecutor.h \
    zsqlquery.h \
    zshortcut.h \
    zlinuxauthenticator.h \
    ztrayicon.h \
    zcountdown.h \
    znotificationdaemon.h \
    znotificationdaemonadaptor.h
SOURCES += zcmcoremodule.cpp \
    zsetting.cpp \
    ztimer.cpp \
    zsysteminfo.cpp \
    zexecutor.cpp \
    zsqlquery.cpp \
    zshortcut.cpp \
    zlinuxauthenticator.cpp \
    ztrayicon.cpp \
    zcountdown.cpp \
    znotificationdaemon.cpp \
    znotificationdaemonadaptor.cpp
DESTDIR = ../../../plugins
TARGET = $$qtLibraryTarget(zcm_core)

QT += xml
QT += sql

#linux-g++ {
    QT += dbus
    LIBS += -lpam \
        -lpam_misc
    HEADERS +=  zdbusinterface.h \
                zdbusabstractadaptor.h
    SOURCES +=  zdbusinterface.cpp \
                zdbusabstractadaptor.cpp
#}
OTHER_FILES +=
