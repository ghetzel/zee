TEMPLATE = lib
MOC_DIR = moc
OBJECTS_DIR = obj
CONFIG += plugin
LIBS += -lvlc
INCLUDEPATH += .
INCLUDEPATH += ../../..

# INCLUDEPATH += /usr/local/include/clutter-1.0
# INCLUDEPATH += /usr/include/pango-1.0
# INCLUDEPATH += /usr/include/glib-2.0
# INCLUDEPATH += /usr/lib/glib-2.0/include
# INCLUDEPATH += /usr/include/cairo
# LIBS += -lclutter-sdl-1.0
# LIBS += -lclutter-qt-1.0
# QMAKE_LFLAGS += -Wl,--no-undefined
HEADERS += ../../zuiutils.h \
    ../../zwidget.h \
    zdevmodule.h \
    zdevlabel.h \
    zvideowidget.h \
    zvlcvideowidget.h \
    zphononvideowidget.h \
    ../../zuiplugin.h \
    ../../../zutil.h
SOURCES += ../../zuiutils.cpp \
    ../../zwidget.cpp \
    zdevmodule.cpp \
    zdevlabel.cpp \
    zvlcvideowidget.cpp \
    zphononvideowidget.cpp \
    ../../../zutil.cpp
TARGET = $$qtLibraryTarget(zmod_dev)
DESTDIR = ../../plugins
QT += xml
QT += svg
QT += declarative
QT += phonon
