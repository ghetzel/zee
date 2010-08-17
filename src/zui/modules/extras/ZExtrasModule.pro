TEMPLATE = lib
MOC_DIR = moc
OBJECTS_DIR = obj
CONFIG += plugin
CONFIG += console
INCLUDEPATH += ./konsole
INCLUDEPATH += .
INCLUDEPATH += ../..
INCLUDEPATH += ../../..
INCLUDEPATH += ../../..
DEPENDPATH += .
DEPENDPATH += ../..
DEPENDPATH += ../../..

HEADERS += zutil.h \
    zuiutils.h \
    zwidget.h \
    zuiplugin.h \
    zlistwidgetitem.h \
    ../form/zlistwidget.h \
    zextrasmodule.h \
    zclock.h \
    zfilebrowser.h \
    zfolderview.h \
    zwebbrowser.h \
    zeventmanager.h \
    zeventrelationship.h \
    zmethodobject.h \
    zeventobject.h \
    zhtmlfolderview.h \
    libzee/zhtmllistmodel.h
SOURCES += zutil.cpp \
    zuiutils.cpp \
    zlistwidgetitem.cpp \
    ../form/zlistwidget.cpp \
    zextrasmodule.cpp \
    zclock.cpp \
    zfilebrowser.cpp \
    zfolderview.cpp \
    zwebbrowser.cpp \
    zeventmanager.cpp \
    zeventrelationship.cpp \
    zmethodobject.cpp \
    zeventobject.cpp \
    zhtmlfolderview.cpp \
    libzee/zhtmllistmodel.cpp
TARGET = $$qtLibraryTarget(zui_extras)
DESTDIR = ../../../plugins
QT += xml
QT += webkit
QT += network


linux-g++{
    DEFINES += HAVE_POSIX_OPENPT
    HEADERS += zterminal.h \
        konsole/Vt102Emulation.h \
        konsole/TerminalDisplay.h \
        konsole/TerminalCharacterDecoder.h \
        konsole/ShellCommand.h \
        konsole/Session.h \
        konsole/ScreenWindow.h \
        konsole/Screen.h \
        konsole/Pty.h \
        konsole/LineFont.h \
        konsole/kpty_p.h \
        konsole/kpty.h \
        konsole/konsole_wcwidth.h \
        konsole/KeyboardTranslator.h \
        konsole/k3processcontroller.h \
        konsole/k3process.h \
        konsole/History.h \
        konsole/Filter.h \
        konsole/ExtendedDefaultTranslator.h \
        konsole/Emulation.h \
        konsole/DefaultTranslatorText.h \
        konsole/ColorTables.h \
        konsole/CharacterColor.h \
        konsole/Character.h \
        konsole/BlockArray.h

    SOURCES += zterminal.cpp \
        konsole/Vt102Emulation.cpp \
        konsole/TerminalDisplay.cpp \
        konsole/TerminalCharacterDecoder.cpp \
        konsole/ShellCommand.cpp \
        konsole/Session.cpp \
        konsole/ScreenWindow.cpp \
        konsole/Screen.cpp \
        konsole/Pty.cpp \
        konsole/kpty.cpp \
        konsole/konsole_wcwidth.cpp \
        konsole/KeyboardTranslator.cpp \
        konsole/k3processcontroller.cpp \
        konsole/k3process.cpp \
        konsole/History.cpp \
        konsole/Filter.cpp \
        konsole/Emulation.cpp \
        konsole/BlockArray.cpp
}
