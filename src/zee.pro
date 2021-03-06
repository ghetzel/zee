# #####################################################################
# Automatically generated by qmake (2.01a) Wed Sep 2 20:48:17 2009
# #####################################################################
TEMPLATE = app
TARGET = zee
MOC_DIR = moc
OBJECTS_DIR = obj
DESTDIR = .
DEPENDPATH += .
INCLUDEPATH += .
DEPENDPATH += ..
INCLUDEPATH += ..
DEPENDPATH += .
INCLUDEPATH += .
QT += xml
QT += sql
QT += svg
QT += network
QT += dbus

CONFIG += static
LIBS += -L$(HOME)/lib
LIBS += -lzee

# QTPLUGIN += qmng qgif
RESOURCES = res/zee.qrc
HEADERS += zevent.h \
    zplugininterface.h \
    zui/zuiplugininterface.h \
    zcm/zcmplugininterface.h \
    zui/zcontainerwidget.h \
    zeventhandler.h \
    zui/zuiutils.h \
    zui/zlistwidgetitem.h \
    zutil.h \
    zui/zuiplugin.h \
    zcm/zcmplugin.h \
    main.h \
    zee.h \
    zmlparser.h \
    zui/layouts/zflowlayout.h \
    zeventmanager.h \
    zeventrelationship.h \
    zconfigurable.h \
    zui/zwidget.h \
    zeventobject.h \
    zmethodobject.h \
    zeeadaptor.h \
    zdbusabstractadaptor.h \
    zui/layouts/zborderlayout.h \
    zcoreapplication.h \
    libzee/zint64.h \
    zconfignode.h \
    zcm/zcomponent.h \
    zcm/zformatterinterface.h \
    zconfigelement.h \
    zui/zstyle.h \
    zui/zstylesection.h \
    zui/zstyleproperty.h
SOURCES += zevent.cpp \
    zutil.cpp \
    main.cpp \
    zui/zuiutils.cpp \
    zui/zlistwidgetitem.cpp \
    zui/zcontainerwidget.cpp \
    zeventhandler.cpp \
    zee.cpp \
    zmlparser.cpp \
    zui/layouts/zflowlayout.cpp \
    zeventmanager.cpp \
    zeventrelationship.cpp \
    zeventobject.cpp \
    zmethodobject.cpp \
    zeeadaptor.cpp \
    zdbusabstractadaptor.cpp \
    zui/layouts/zborderlayout.cpp \
    libzee/zint64.cpp \
    zconfignode.cpp \
    zconfigelement.cpp \
    zui/zstyle.cpp \
    zui/zstylesection.cpp \
    zui/zstyleproperty.cpp
OTHER_FILES += theme.qss \
    dev/ideaman \
    theme.qss.orig \
    theme.qss.debug \
    zui-def.xml.test1 \
    zui-def.xml.debug \
    zui-def.xml.full \
    zui-def.xml.fulltest \
    gfx/bubbles.svg \
    gfx/spheres.svg \
    gfx/cubic.svg \
    zonky.xml \
    sidebar.xml \
    zde.xml \
    zui-def.xml \
    ../doc/zee.css \
    zcm.pri
#linux-g++ {
    INCLUDEPATH += /usr/include/
    LIBS += -lX11
    QT += dbus
    HEADERS += zui/zx11/zxwindow.h \
        zui/zx11/zxserver.h \
        zui/zx11/zxrootwindow.h \
        zui/zx11/zxevent.h
    SOURCES += zui/zx11/zxwindow.cpp \
        zui/zx11/zxserver.cpp \
        zui/zx11/zxrootwindow.cpp \
        zui/zx11/zxevent.cpp
#}
win32 {
    CONFIG += console
    CONFIG += debug
}
