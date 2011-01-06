HEADERS += zdebug.h \
    zutil.cpp \
    zstyle.h \
    zstylesection.h \
    zstyleproperty.h
SOURCES += zdebug.cpp \
    main.cpp \
    zutil.cpp \
    zstyle.cpp \
    zstylesection.cpp \
    zstyleproperty.cpp

LIBS += -L$(HOME)/lib
LIBS += -lzee

INCLUDEPATH += .
INCLUDEPATH += ..
INCLUDEPATH += ../zui
DEPENDPATH  += .
DEPENDPATH  += ..
DEPENDPATH  += ../zui
