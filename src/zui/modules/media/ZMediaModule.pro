TEMPLATE = lib
MOC_DIR = moc
OBJECTS_DIR = obj
CONFIG += plugin
CONFIG += console
INCLUDEPATH += .
INCLUDEPATH += ../../..
DEPENDPATH += .
DEPENDPATH += ../..
DEPENDPATH += ../../..
HEADERS += zuiutils.h \
    zmediamodule.h \
    zuiplugin.h \
    zwidget.h \
    zutil.h \
    zeventmanager.h \
    zeventrelationship.h \
    zmethodobject.h \
    zeventobject.h \
    zseekbar.h
SOURCES += zuiutils.cpp \
    zmediamodule.cpp \
    zutil.cpp \
    zeventmanager.cpp \
    zeventrelationship.cpp \
    zmethodobject.cpp \
    zeventobject.cpp \
    zseekbar.cpp
TARGET = $$qtLibraryTarget(zui_media)
DESTDIR = ../../../plugins
QT += xml
