TEMPLATE = app
TARGET = dbustest
MOC_DIR = moc
OBJECTS_DIR = obj
DESTDIR = .
DEPENDPATH += .
INCLUDEPATH += .

QT +=		dbus

HEADERS +=	zdbusinterface.h
SOURCES +=	zdbusinterface.cpp \
		main.cpp
