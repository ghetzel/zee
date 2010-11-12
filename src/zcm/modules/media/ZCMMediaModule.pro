TEMPLATE = lib
MOC_DIR = moc
OBJECTS_DIR = obj
CONFIG += plugin
CONFIG += console
INCLUDEPATH += .
INCLUDEPATH += ../../..
DEPENDPATH += ../../../
LIBS += -L/usr/lib \
    -ltag
QMAKE_LIBS += -ltag
QMAKE_CXXFLAGS += -I/usr/include
include(../../../zcm.pri)
HEADERS += zcmmediamodule.h \
    zaudiomanager.h \
    zmetareader.h \
    zmetaparser.h \
    metaparsers/zaudiometaparser.h \
    zmetareaderadaptor.h \
    zsound.h
SOURCES += zcmmediamodule.cpp \
    zaudiomanager.cpp \
    zmetareader.cpp \
    metaparsers/zaudiometaparser.cpp \
    zmetareaderadaptor.cpp \
    zsound.cpp
TARGET = $$qtLibraryTarget(zcm_media)
DESTDIR = ../../../plugins
QT += xml
QT += phonon
QT += dbus
#linux-g++ {
    INCLUDEPATH += /usr/include/KDE/
    HEADERS += zaudioadaptor.h \
        zdbusabstractadaptor.h
    SOURCES += zaudioadaptor.cpp \
        zdbusabstractadaptor.cpp

#}
