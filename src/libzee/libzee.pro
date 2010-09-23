TEMPLATE = lib
TARGET = zee
MOC_DIR = moc
OBJECTS_DIR = obj
DESTDIR = lib
DEPENDPATH += .
INCLUDEPATH += .
CONFIG += console
QT += network
LIBS += -lboost_date_time
HEADERS += zlinuxfilenotifier.h \
    zfilenotifier.h \
    zlocalsystem.h \
    zhtmllistmodel.h \
    zint64.h \
    zdatetime.h \
    libzee.h
SOURCES += zlinuxfilenotifier.cpp \
    zlocalsystem.cpp \
    zhtmllistmodel.cpp \
    zint64.cpp \
    zdatetime.cpp
