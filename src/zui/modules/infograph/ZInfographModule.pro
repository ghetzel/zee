include(../../../zui.pri)
TARGET =    $$qtLibraryTarget(zui_infograph)

QT +=       svg

HEADERS +=  zinfographmodule.h      \
            zgenericdial.h          \
            zgauge.h                \
            zpiegauge.h             \
            zpolystateindicator.h   \
            zcharacterdisplay.h

SOURCES +=  zinfographmodule.cpp    \
            zgenericdial.cpp        \
            zgauge.cpp              \
            zpiegauge.cpp           \
            zpolystateindicator.cpp \
            zcharacterdisplay.cpp
