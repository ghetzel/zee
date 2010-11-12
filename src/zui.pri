TEMPLATE =      lib
MOC_DIR =       moc
OBJECTS_DIR =   obj
CONFIG +=       plugin
CONFIG +=       console
INCLUDEPATH +=  .
INCLUDEPATH +=  ../../..
DEPENDPATH +=   ..
DEPENDPATH +=   ../..
DEPENDPATH +=   ../../..
RESOURCES =     res/zee.qrc
DESTDIR =       ../../../plugins

QT +=           xml

LIBS +=         -L$(HOME)/lib
LIBS +=         -lzee

HEADERS +=      zutil.h                         \
                zuiplugin.h                     \
                zuiutils.h                      \
                zwidget.h                       \
                zui/zcontainerwidget.h          \
                zeventmanager.h                 \
                zeventrelationship.h            \
                zmethodobject.h                 \
                zeventobject.h                  \
                zui/layouts/zflowlayout.h       \
                zui/layouts/zborderlayout.h     \
                zcm/zformatterinterface.h

SOURCES +=      zutil.cpp                       \
                zuiutils.cpp                    \
                zui/zcontainerwidget.cpp        \
                zeventmanager.cpp               \
                zeventrelationship.cpp          \
                zmethodobject.cpp               \
                zeventobject.cpp                \
                zui/layouts/zflowlayout.cpp     \
                zui/layouts/zborderlayout.cpp
