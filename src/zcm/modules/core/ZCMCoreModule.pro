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
LIBS += -lsigar -lboost_date_time
HEADERS += zcmcoremodule.h \
    zsetting.h \
    ztimer.h \
    zsysteminfo.h \
    zexecutor.h \
    zsqlquery.h \
    zshortcut.h \
    zlinuxauthenticator.h \
    ztrayicon.h \
    zcountdown.h
SOURCES += zcmcoremodule.cpp \
    zsetting.cpp \
    ztimer.cpp \
    zsysteminfo.cpp \
    zexecutor.cpp \
    zsqlquery.cpp \
    zshortcut.cpp \
    zlinuxauthenticator.cpp \
    ztrayicon.cpp \
    zcountdown.cpp
DESTDIR = ../../../plugins
TARGET = $$qtLibraryTarget(zcm_core)
QT += xml \
    sql
linux-g++ { 
    QT += dbus
    LIBS += -lpam \
        -lpam_misc
    HEADERS += zdbusinterface.h
    SOURCES += zdbusinterface.cpp
}
OTHER_FILES += 
