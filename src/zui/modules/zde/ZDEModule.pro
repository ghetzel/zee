TEMPLATE = lib
MOC_DIR = moc
OBJECTS_DIR = obj
CONFIG += plugin
INCLUDEPATH += .
INCLUDEPATH += ../..
INCLUDEPATH += ../../..
DEPENDPATH += .
DEPENDPATH += ../..
DEPENDPATH += ../../..

HEADERS +=  zuiutils.h \
            zwidget.h \
            zuiplugin.h \
            zevent.h \
            zeventmanager.h \
            zeventrelationship.h \
            zmethodobject.h \
            zeventobject.h \
            zuiplugininterface.h \
            zutil.h \
            zdemodule.h \
            ztaskbar.h \
            zxwindowlistitem.h \
            zxwindowlistmodel.h \
            zx11/zxwindow.h \
            zx11/zxserver.h \
            zx11/zxrootwindow.h \
            zx11/zxevent.h
SOURCES +=  zuiutils.cpp \
            zevent.cpp \
            zeventmanager.cpp \
            zeventrelationship.cpp \
            zmethodobject.cpp \
            zeventobject.cpp \
            zutil.cpp \
            zdemodule.cpp \
            ztaskbar.cpp \
            zxwindowlistitem.cpp \
            zxwindowlistmodel.cpp \
            zx11/zxwindow.cpp \
            zx11/zxserver.cpp \
            zx11/zxrootwindow.cpp \
            zx11/zxevent.cpp
TARGET = $$qtLibraryTarget(zui_zde)
DESTDIR = ../../../plugins
QT += xml
