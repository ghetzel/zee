TEMPLATE = lib
MOC_DIR = moc
OBJECTS_DIR = obj
CONFIG += plugin
INCLUDEPATH += .
INCLUDEPATH += ../..
INCLUDEPATH += ../../..
DEPENDPATH  += .
DEPENDPATH  += ../..
DEPENDPATH  += ../../..
HEADERS += zutil.h \
    zeventmanager.h \
    zeventobject.h \
    #zcontainerwidget.h \
    zmethodobject.h \
    zuiutils.h \
    zuiplugin.h \
    zinfographmodule.h \
    zgenericdial.h \
    zpolystateindicator.h \
    zgauge.h \
    zpiegauge.h \
    zcharacterdisplay.h \
    zui/layouts/zflowlayout.h
SOURCES += zutil.cpp \
    zeventmanager.cpp \
    zeventobject.cpp \
    #zcontainerwidget.cpp \
    zmethodobject.cpp \
    zuiutils.cpp \
    zinfographmodule.cpp \
    zgenericdial.cpp \
    zpolystateindicator.cpp \
    zgauge.cpp \
    zpiegauge.cpp \
    zcharacterdisplay.cpp \
    zui/layouts/zflowlayout.cpp
TARGET = $$qtLibraryTarget(zui_infograph)
DESTDIR = ../../../plugins
QT += xml
QT += svg
LIBS += -lzee
