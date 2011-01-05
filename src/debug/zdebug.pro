HEADERS += zdebug.h \
    zutil.cpp \
    zssparser.h
SOURCES += zdebug.cpp \
    main.cpp \
    zutil.cpp \
    zssparser.cpp

LIBS += -L$(HOME)/lib
LIBS += -lzee

INCLUDEPATH += .
INCLUDEPATH += ..
INCLUDEPATH += ../zui
DEPENDPATH  += .
DEPENDPATH  += ..
DEPENDPATH  += ../zui
