HEADERS +=  zutil.h                       \
            zeventmanager.h               \
            zplugininterface.h            \
            zeventrelationship.h          \
            zmethodobject.h               \
            zeventobject.h                \
            zui/zuiutils.h                \
            zui/zwidget.h                 \
            zui/layouts/zflowlayout.h     \
            zui/layouts/zborderlayout.h   \
            zcm/zcmplugin.h               \
            zcm/zcmplugininterface.h      \
            zcm/zformatterinterface.h     \
            zcm/zcomponent.h

SOURCES +=  zutil.cpp                     \
            zeventmanager.cpp             \
            zeventrelationship.cpp        \
            zmethodobject.cpp             \
            zeventobject.cpp              \
            zui/zuiutils.cpp              \
            zui/layouts/zflowlayout.cpp   \
            zui/layouts/zborderlayout.cpp

LIBS +=     -L$(HOME)/lib
LIBS +=     -lzee
