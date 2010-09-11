TEMPLATE = lib
MOC_DIR = moc
OBJECTS_DIR = obj
CONFIG += plugin
CONFIG += console
INCLUDEPATH += .
INCLUDEPATH += ..
INCLUDEPATH += ../..
INCLUDEPATH += ../../..
DEPENDPATH += .
DEPENDPATH += ..
DEPENDPATH += ../..
DEPENDPATH += ../../..
HEADERS += zuiutils.h \
    form/zprogressbar.h \
    zmediamodule.h \
    zuiplugin.h \
    zwidget.h \
    zutil.h \
    zeventmanager.h \
    zeventrelationship.h \
    zmethodobject.h \
    zeventobject.h \
    zseekbar.h \
    zvideowidget.h
SOURCES += zuiutils.cpp \
    form/zprogressbar.cpp \
    zmediamodule.cpp \
    zutil.cpp \
    zeventmanager.cpp \
    zeventrelationship.cpp \
    zmethodobject.cpp \
    zeventobject.cpp \
    zseekbar.cpp \
    zvideowidget.cpp
TARGET = $$qtLibraryTarget(zui_media)
DESTDIR = ../../../plugins
QT += xml
QT += phonon
QT += opengl
QT += network
CONFIG += pipemode

include(qmpwidget.pri)
