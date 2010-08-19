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
HEADERS += zuiutils.h \
    zformmodule.h \
    zbutton.h \
    zlistwidget.h \
    zuiplugin.h \
    zwidget.h \
    zutil.h \
    zeventmanager.h \
    zeventrelationship.h \
    zcheckbox.h \
    zradiobutton.h \
    ztextinput.h \
    zslider.h \
    zprogressbar.h \
    zmethodobject.h \
    zeventobject.h \
    ztogglebutton.h \
    ztuplelistmodel.h \
    ztableview.h \
    zframe.h
SOURCES += zuiutils.cpp \
    zui/layouts/zflowlayout.cpp \
    zformmodule.cpp \
    zbutton.cpp \
    zlistwidget.cpp \
    zutil.cpp \
    zeventmanager.cpp \
    zeventrelationship.cpp \
    zcheckbox.cpp \
    zradiobutton.cpp \
    ztextinput.cpp \
    zslider.cpp \
    zprogressbar.cpp \
    zmethodobject.cpp \
    zeventobject.cpp \
    ztogglebutton.cpp \
    ztuplelistmodel.cpp \
    ztableview.cpp \
    zframe.cpp
TARGET = $$qtLibraryTarget(zui_form)
DESTDIR = ../../../plugins
QT += xml
