TEMPLATE = lib
TARGET = zee
MOC_DIR = moc
OBJECTS_DIR = obj
DESTDIR = lib
DEPENDPATH += .
INCLUDEPATH += .
CONFIG += console
CONFIG += static
HEADERS += zlinuxfilenotifier.h \
    zfilenotifier.h \
    zlocalsystem.h
SOURCES += zlinuxfilenotifier.cpp \
    zlocalsystem.cpp
