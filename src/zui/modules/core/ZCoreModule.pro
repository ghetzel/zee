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
    zui/zcontainerwidget.h \
    zui/layouts/zflowlayout.h \
    zui/layouts/zborderlayout.h \
    zcoremodule.h \
    zscreenmanager.h \
    zuiplugin.h \
    zwidget.h \
    zutil.h \
    zeventmanager.h \
    zeventrelationship.h \
    zmethodobject.h \
    zeventobject.h \
    zscreen.h \
    zlabel.h \
    zroot.h \
    zwindow.h \
    zspacer.h \
    zsplitter.h \
    zimage.h \
    zmenu.h \
    zcontainer.h
SOURCES += zuiutils.cpp \
    zui/zcontainerwidget.cpp \
    zui/layouts/zflowlayout.cpp \
    zui/layouts/zborderlayout.cpp \
    zcoremodule.cpp \
    zscreenmanager.cpp \
    zutil.cpp \
    zeventmanager.cpp \
    zeventrelationship.cpp \
    zscreen.cpp \
    zlabel.cpp \
    zwindow.cpp \
    zmethodobject.cpp \
    zeventobject.cpp \
    zspacer.cpp \
    zsplitter.cpp \
    zimage.cpp \
    zmenu.cpp \
    zcontainer.cpp
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
