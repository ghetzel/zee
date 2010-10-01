include(../../../zui.pri)

TARGET =    $$qtLibraryTarget(zui_zde)

HEADERS +=  zdemodule.h \
            zevent.h \
            ztaskbar.h \
            zxwindowlistitem.h \
            zxwindowlistmodel.h \
            zx11/zxwindow.h \
            zx11/zxserver.h \
            zx11/zxrootwindow.h \
            zx11/zxevent.h

SOURCES +=  zdemodule.cpp \
            zevent.cpp \
            ztaskbar.cpp \
            zxwindowlistitem.cpp \
            zxwindowlistmodel.cpp \
            zx11/zxwindow.cpp \
            zx11/zxserver.cpp \
            zx11/zxrootwindow.cpp \
            zx11/zxevent.cpp

