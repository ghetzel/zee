TEMPLATE = lib
MOC_DIR = moc
OBJECTS_DIR = obj
CONFIG += plugin
CONFIG += console
INCLUDEPATH += .
INCLUDEPATH += ../../..
HEADERS += ../../zuiutils.h \
    ../../../zui/layouts/zflowlayout.h \
    zcoremodule.h \
    zscreenmanager.h \
    ../../zuiplugin.h \
    ../../zwidget.h \
    ../../zroot.h \
    ../../../zutil.h \
    ../../../zeventmanager.h \
    ../../../zeventrelationship.h \
    ../../../zmethodobject.h \
    ../../../zeventobject.h \
    zcontainerwidget.h \
    zscreen.h \
    zlabel.h \
    zwindow.h
SOURCES += ../../zuiutils.cpp \
    ../../../zui/layouts/zflowlayout.cpp \
    zcoremodule.cpp \
    zscreenmanager.cpp \
    ../../../zutil.cpp \
    ../../../zeventmanager.cpp \
    ../../../zeventrelationship.cpp \
    zcontainerwidget.cpp \
    zscreen.cpp \
    zlabel.cpp \
    zwindow.cpp \
    ../../../zmethodobject.cpp \
    ../../../zeventobject.cpp
linux-g++ { 
    HEADERS += ../../../zui/zx11/zxrootwindow.h \
        ../../../zui/zx11/zxwindow.h \
        ../../../zui/zx11/zxserver.h \
        ../../../zui/zx11/zxevent.h
    SOURCES += ../../../zui/zx11/zxrootwindow.cpp \
        ../../../zui/zx11/zxwindow.cpp \
        ../../../zui/zx11/zxserver.cpp \
        ../../../zui/zx11/zxevent.cpp
}
TARGET = $$qtLibraryTarget(zui_core)
DESTDIR = ../../../plugins
QT += xml
