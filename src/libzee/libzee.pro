TEMPLATE = lib
TARGET = zee
MOC_DIR = moc
OBJECTS_DIR = obj
DESTDIR = lib
DEPENDPATH += .
INCLUDEPATH += .
CONFIG += console
QT += network
HEADERS += zlinuxfilenotifier.h \
    zfilenotifier.h \
    zlocalsystem.h \
    zhtmllistmodel.h \
    zint64.h \
    php-timelib/timelib_structs.h \
    php-timelib/timelib.h \
    php-timelib/timelib_config.h \
    zdatetime.h \
    libzee.h
SOURCES += zlinuxfilenotifier.cpp \
    zlocalsystem.cpp \
    zhtmllistmodel.cpp \
    zint64.cpp \
    php-timelib/timelib.c \
    php-timelib/parse_date.c \
    zdatetime.cpp
