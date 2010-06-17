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
    zutil.h \
    zplugininterface.h \
    zeventmanager.h \
    zeventrelationship.h \
    zmethodobject.h \
    zeventobject.h \
    zmetareader.h \
    zmetadata.h \
    metareaders/zaudiometadata.h
SOURCES += zcmmediamodule.cpp \
    zaudiomanager.cpp \
    zutil.cpp \
    zeventmanager.cpp \
    zeventrelationship.cpp \
    zmethodobject.cpp \
    zeventobject.cpp \
    zmetareader.cpp \
    metareaders/zaudiometadata.cpp
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
