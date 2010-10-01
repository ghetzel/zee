include(../../../zui.pri)

TARGET =    $$qtLibraryTarget(zui_core)

HEADERS +=  zcoremodule.h       \
            zscreenmanager.h    \
            zroot.h             \
            zcontainer.h        \
            zscreen.h           \
            zlabel.h            \
            zwindow.h           \
            zspacer.h           \
            zsplitter.h         \
            zimage.h            \
            zmenu.h

SOURCES +=  zcoremodule.cpp     \
            zscreenmanager.cpp  \
            zcontainer.cpp      \
            zscreen.cpp         \
            zlabel.cpp          \
            zwindow.cpp         \
            zspacer.cpp         \
            zsplitter.cpp       \
            zimage.cpp          \
            zmenu.cpp

linux-g++ { 
    HEADERS += zui/zx11/zxrootwindow.h \
        zui/zx11/zxwindow.h \
        zui/zx11/zxserver.h \
        zui/zx11/zxevent.h
    SOURCES += zui/zx11/zxrootwindow.cpp \
        zui/zx11/zxwindow.cpp \
        zui/zx11/zxserver.cpp \
        zui/zx11/zxevent.cpp
}
