#include "zdbusabstractadaptor.h"

ZDBusAbstractAdaptor::ZDBusAbstractAdaptor(QObject *parent)
    : QDBusAbstractAdaptor(parent){
#ifdef ZDBUS_NAME
    _name = ZDBUS_NAME;
#endif
    _instance = parent;
}

ZDBusAbstractAdaptor::ZDBusAbstractAdaptor(QString name, QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
    if(!name.isEmpty())
        _name = name;
    _instance = NULL;
}

void ZDBusAbstractAdaptor::setInstance(QObject *instance){
    _instance = instance;
}

void ZDBusAbstractAdaptor::registerService()
{
#ifdef ZDBUS_NAME
//  if name isn't set yet...
    if(_name.isEmpty())
        if(_instance && !_instance->objectName().isEmpty())
            _name = _instance->objectName();

    if(_instance){
        QDBusConnection::sessionBus().registerObject(ZDBUS_OPATH+_name,
                                                     _instance);
        QDBusConnection::sessionBus().registerService(ZDBUS_SVCNM);
    }
#endif
}
