include(../../../zui.pri)
TARGET =    $$qtLibraryTarget(zui_form)

HEADERS +=  zformmodule.h       \
            zbutton.h           \
            zframe.h            \
            ztextinput.h        \
            zcheckbox.h         \
            zradiobutton.h      \
            zslider.h           \
            zprogressbar.h      \
            ztogglebutton.h     \
            zlistwidget.h       \
            ztuplelistmodel.h   \
            ztableview.h

SOURCES +=  zformmodule.cpp     \
            zbutton.cpp         \
            zframe.cpp          \
            ztextinput.cpp      \
            zcheckbox.cpp       \
            zradiobutton.cpp    \
            zslider.cpp         \
            zprogressbar.cpp    \
            ztogglebutton.cpp   \
            zlistwidget.cpp     \
            ztuplelistmodel.cpp \
            ztableview.cpp
