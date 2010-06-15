# include(../../../../qmapcontrol/QMapControl/QMapControl.pri)
TEMPLATE = lib
MOC_DIR = moc
OBJECTS_DIR = obj
CONFIG += plugin

# DEPENDPATH += ../../../../qmapcontrol/QMapControl/src
INCLUDEPATH += .
INCLUDEPATH += ../../..

# INCLUDEPATH += ../../../../qmapcontrol
HEADERS += ../../zuiutils.h \
    ../../zuiplugin.h \
    znavmodule.h \
    zroadsignwidget.h \
    zmapinfowidget.h \
    zmapwidget/slippymap.h \
    zmapwidget/zmapwidget.h
SOURCES += ../../zuiutils.cpp \
    znavmodule.cpp \
    zroadsignwidget.cpp \
    zmapinfowidget.cpp \
    zmapwidget/slippymap.cpp \
    zmapwidget/zmapwidget.cpp
TARGET = $$qtLibraryTarget(zmod_nav)
DESTDIR = ../../plugins
QT += xml
QT += declarative
QT += network
