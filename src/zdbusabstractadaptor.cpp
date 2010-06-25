#include "zdbusabstractadaptor.h"

ZDBusAbstractAdaptor::ZDBusAbstractAdaptor(QObject *parent)
    : QDBusAbstractAdaptor(parent){
    _instance = parent;
}

ZDBusAbstractAdaptor::ZDBusAbstractAdaptor(QString name, QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
    if(!name.isEmpty())
        _name = name;
    _instance = parent;
}

void ZDBusAbstractAdaptor::setInstance(QObject *instance){
    _instance = instance;
}

void ZDBusAbstractAdaptor::registerService()
{
//  if name isn't set yet...
    if(_name.isEmpty())
        if(_instance && !_instance->objectName().isEmpty())
            _name = _instance->objectName();

    if(_instance){
        QDBusConnection::sessionBus().registerObject(ZDBUS_OPATH+_name,
                                                     _instance);
        QDBusConnection::sessionBus().registerService(ZDBUS_SVCNM);
        //+zApp->arg("program").toString()
    }
}
