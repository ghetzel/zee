HEADERS +=  zee.h                         \
            zutil.h                       \
            zeventmanager.h               \
            zplugininterface.h            \
            zeventrelationship.h          \
            zmethodobject.h               \
            zeventobject.h                \
            zui/zuiutils.h                \
            zui/zuiparser.h               \
            zui/zwidget.h                 \
            zui/layouts/zflowlayout.h     \
            zui/layouts/zborderlayout.h   \
            zcm/zcmplugin.h               \
            zcm/zcmplugininterface.h

SOURCES +=  zee.cpp                       \
            zutil.cpp                     \
            zeventmanager.cpp             \
            zeventrelationship.cpp        \
            zmethodobject.cpp             \
            zeventobject.cpp              \
            zui/zuiutils.cpp              \
            zui/zuiparser.cpp             \
            zui/layouts/zflowlayout.cpp   \
            zui/layouts/zborderlayout.cpp

LIBS +=     -lzee

