HEADERS += zdebug.h \
    zutil.cpp
SOURCES += zdebug.cpp \
    main.cpp \
    zutil.cpp

LIBS += -L$(HOME)/lib
LIBS += -lzee

INCLUDEPATH += .
INCLUDEPATH += ..
DEPENDPATH  += .
DEPENDPATH  += ..
