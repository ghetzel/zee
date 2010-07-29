TEMPLATE = lib
MOC_DIR = moc
OBJECTS_DIR = obj
CONFIG += plugin
CONFIG += console
INCLUDEPATH += .
INCLUDEPATH += ../../..
INCLUDEPATH += /usr/include
DEPENDPATH += ../../../
LIBS += -L/usr/lib \
    -ltag
QMAKE_LIBS += -ltag
QMAKE_CXXFLAGS += -I/usr/include
HEADERS += zcmmediamodule.h \
    zaudiomanager.h \
    zcm/zcmplugin.h \
    zcm/zcmplugininterface.h \
    zee.h \
    zutil.h \
    zui/zuiparser.h \
    zui/zuiutils.h \
    zplugininterface.h \
    zeventmanager.h \
    zeventrelationship.h \
    zmethodobject.h \
    zeventobject.h \
    zmetareader.h \
    zmetaparser.h \
    metaparsers/zaudiometaparser.h
SOURCES += zcmmediamodule.cpp \
    zaudiomanager.cpp \
    zee.cpp \
    zutil.cpp \
    zui/zuiparser.cpp \
    zui/zuiutils.cpp \
    zeventmanager.cpp \
    zeventrelationship.cpp \
    zmethodobject.cpp \
    zeventobject.cpp \
    zmetareader.cpp \
    metaparsers/zaudiometaparser.cpp
TARGET = $$qtLibraryTarget(zcm_media)
DESTDIR = ../../../plugins
QT += xml
QT += phonon
linux-g++ {
    HEADERS +=  zaudioadaptor.h \
                zdbusabstractadaptor.h
    SOURCES +=  zaudioadaptor.cpp \
                zdbusabstractadaptor.cpp
    QT += dbus
}
