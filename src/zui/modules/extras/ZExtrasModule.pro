TEMPLATE = lib
MOC_DIR = moc
OBJECTS_DIR = obj
CONFIG += plugin
CONFIG += console
INCLUDEPATH += .
INCLUDEPATH += ../..
INCLUDEPATH += ../../..
DEPENDPATH += .
DEPENDPATH += ../..
DEPENDPATH += ../../..

HEADERS += zutil.h \
    zuiutils.h \
    zwidget.h \
    zuiplugin.h \
    zlistwidgetitem.h \
    ../form/zlistwidget.h \
    zextrasmodule.h \
    zclock.h \
    zfilebrowser.h \
    zfolderview.h \
    zwebbrowser.h \
    zeventmanager.h \
    zeventrelationship.h \
    zmethodobject.h \
    zeventobject.h \
    zhtmlfolderview.h \
    libzee/zhtmllistmodel.h
SOURCES += zutil.cpp \
    zuiutils.cpp \
    zlistwidgetitem.cpp \
    ../form/zlistwidget.cpp \
    zextrasmodule.cpp \
    zclock.cpp \
    zfilebrowser.cpp \
    zfolderview.cpp \
    zwebbrowser.cpp \
    zeventmanager.cpp \
    zeventrelationship.cpp \
    zmethodobject.cpp \
    zeventobject.cpp \
    zhtmlfolderview.cpp \
    libzee/zhtmllistmodel.cpp
TARGET = $$qtLibraryTarget(zui_extras)
DESTDIR = ../../../plugins
QT += xml
QT += webkit
QT += network
