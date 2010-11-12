include(../../../zui.pri)
TARGET =    $$qtLibraryTarget(zui_extras)
QT +=       webkit
QT +=       network

HEADERS +=  zextrasmodule.h         \
            zlistwidgetitem.h       \
            ../form/zlistwidget.h   \
            zclock.h                \
            zfilebrowser.h          \
            zfolderview.h           \
            zwebbrowser.h           \
            zhtmlfolderview.h

SOURCES +=  zextrasmodule.cpp       \
            zlistwidgetitem.cpp     \
            ../form/zlistwidget.cpp \
            zclock.cpp              \
            zfilebrowser.cpp        \
            zfolderview.cpp         \
            zwebbrowser.cpp         \
            zhtmlfolderview.cpp

#linux-g++ {
    INCLUDEPATH += ./qtermwidget
    DEFINES += HAVE_POSIX_OPENPT
    HEADERS += zterminal.h \
        qtermwidget/Vt102Emulation.h \
        qtermwidget/TerminalDisplay.h \
        qtermwidget/TerminalCharacterDecoder.h \
        qtermwidget/ShellCommand.h \
        qtermwidget/Session.h \
        qtermwidget/ScreenWindow.h \
        qtermwidget/Screen.h \
        qtermwidget/qtermwidget.h \
        qtermwidget/Pty.h \
        qtermwidget/LineFont.h \
        qtermwidget/kpty_p.h \
        qtermwidget/kpty.h \
        qtermwidget/konsole_wcwidth.h \
        qtermwidget/KeyboardTranslator.h \
        qtermwidget/k3processcontroller.h \
        qtermwidget/k3process.h \
        qtermwidget/History.h \
        qtermwidget/Filter.h \
        qtermwidget/ExtendedDefaultTranslator.h \
        qtermwidget/Emulation.h \
        qtermwidget/DefaultTranslatorText.h \
        qtermwidget/ColorTables.h \
        qtermwidget/CharacterColor.h \
        qtermwidget/Character.h \
        qtermwidget/BlockArray.h
    SOURCES += zterminal.cpp \
        qtermwidget/Vt102Emulation.cpp \
        qtermwidget/TerminalDisplay.cpp \
        qtermwidget/TerminalCharacterDecoder.cpp \
        qtermwidget/ShellCommand.cpp \
        qtermwidget/Session.cpp \
        qtermwidget/ScreenWindow.cpp \
        qtermwidget/Screen.cpp \
        qtermwidget/qtermwidget.cpp \
        qtermwidget/Pty.cpp \
        qtermwidget/kpty.cpp \
        qtermwidget/konsole_wcwidth.cpp \
        qtermwidget/KeyboardTranslator.cpp \
        qtermwidget/k3processcontroller.cpp \
        qtermwidget/k3process.cpp \
        qtermwidget/History.cpp \
        qtermwidget/Filter.cpp \
        qtermwidget/Emulation.cpp \
        qtermwidget/BlockArray.cpp
#}
