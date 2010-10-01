include(../../../zui.pri)
TARGET =    $$qtLibraryTarget(zui_media)

QT +=       phonon
QT +=       opengl
QT +=       network


HEADERS +=  zmediamodule.h          \
            zseekbar.h              \
            zvideowidget.h          \
            form/zprogressbar.h

SOURCES +=  zmediamodule.cpp        \
            zseekbar.cpp            \
            zvideowidget.cpp        \
            form/zprogressbar.cpp

CONFIG +=   pipemode
include(qmpwidget.pri)
