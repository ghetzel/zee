TEMPLATE = lib
MOC_DIR = moc
OBJECTS_DIR = obj
CONFIG += plugin
CONFIG += console
INCLUDEPATH += .
INCLUDEPATH += ../../..
HEADERS += ../../../zutil.h \
    ../../zuiutils.h \
    ../../zwidget.h \
    ../../zuiplugin.h \
    ../../zlistwidgetitem.h \
    ../form/zlistwidget.h \
    zextrasmodule.h \
    zclock.h \
    zfilebrowser.h \
    zfolderview.h \
    zwebbrowser.h \
    ../../../zeventmanager.h \
    ../../../zeventrelationship.h \
    ../../../zmethodobject.h \
    ../../../zeventobject.h
SOURCES += ../../../zutil.cpp \
    ../../zuiutils.cpp \
    ../../zlistwidgetitem.cpp \
    ../form/zlistwidget.cpp \
    zextrasmodule.cpp \
    zclock.cpp \
    zfilebrowser.cpp \
    zfolderview.cpp \
    zwebbrowser.cpp \
    ../../../zeventmanager.cpp \
    ../../../zeventrelationship.cpp \
    ../../../zmethodobject.cpp \
    ../../../zeventobject.cpp
TARGET = $$qtLibraryTarget(zui_extras)
DESTDIR = ../../../plugins
QT += xml
QT += webkit
