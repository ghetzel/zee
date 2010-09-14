TEMPLATE = lib
TARGET = zee
MOC_DIR = moc
OBJECTS_DIR = obj
DESTDIR = lib
DEPENDPATH += .
INCLUDEPATH += .
CONFIG += console
CONFIG += static
QT += network
HEADERS += zlinuxfilenotifier.h \
    zfilenotifier.h \
    zlocalsystem.h \
    zhtmllistmodel.h \
    zint64.h
SOURCES += zlinuxfilenotifier.cpp \
    zlocalsystem.cpp \
    zhtmllistmodel.cpp \
    zint64.cpp
