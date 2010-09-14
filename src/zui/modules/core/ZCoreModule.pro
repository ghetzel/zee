TEMPLATE = lib
MOC_DIR = moc
OBJECTS_DIR = obj
CONFIG += plugin
CONFIG += console
INCLUDEPATH += .
INCLUDEPATH += ../../..
DEPENDPATH += ../..
DEPENDPATH += ../../..
RESOURCES = res/zee.qrc
HEADERS += zuiutils.h \
    zui/layouts/zflowlayout.h \
    zui/layouts/zborderlayout.h \
    zcoremodule.h \
    zscreenmanager.h \
    zuiplugin.h \
    zwidget.h \
    zroot.h \
    zutil.h \
    zeventmanager.h \
    zeventrelationship.h \
    zmethodobject.h \
    zeventobject.h \
    zcontainerwidget.h \
    zscreen.h \
    zlabel.h \
    zwindow.h \
    zspacer.h \
    zsplitter.h
SOURCES += zuiutils.cpp \
    zui/layouts/zflowlayout.cpp \
    zui/layouts/zborderlayout.cpp \
    zcoremodule.cpp \
    zscreenmanager.cpp \
    zutil.cpp \
    zeventmanager.cpp \
    zeventrelationship.cpp \
    zcontainerwidget.cpp \
    zscreen.cpp \
    zlabel.cpp \
    zwindow.cpp \
    zmethodobject.cpp \
    zeventobject.cpp \
    zspacer.cpp \
    zsplitter.cpp
linux-g++ { 
    HEADERS += zui/zx11/zxrootwindow.h \
        zui/zx11/zxwindow.h \
        zui/zx11/zxserver.h \
        zui/zx11/zxevent.h
    SOURCES += zui/zx11/zxrootwindow.cpp \
        zui/zx11/zxwindow.cpp \
        zui/zx11/zxserver.cpp \
        zui/zx11/zxevent.cpp
}
TARGET = $$qtLibraryTarget(zui_core)
DESTDIR = ../../../plugins
QT += xml
