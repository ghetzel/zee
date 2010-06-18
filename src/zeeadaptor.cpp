#include "zeeadaptor.h"

ZeeAdaptor::ZeeAdaptor(Zee *parent)
    : ZDBusAbstractAdaptor(parent)
{
    init();
}

ZeeAdaptor::ZeeAdaptor(QString name, Zee *parent)
    : ZDBusAbstractAdaptor(name, parent){
    init();
}

void ZeeAdaptor::init(){
    registerService();

    connect(instance(), SIGNAL(styleReloaded()),
            this, SIGNAL(styleReloaded()));
}

Zee *ZeeAdaptor::instance(){
    return QCAST(Zee*,ZDBusAbstractAdaptor::instance());
}



void ZeeAdaptor::reloadStyleSheet(){
    if(instance())
        instance()->reloadStyleSheet();
}

void ZeeAdaptor::log(QString msg){
    if(instance())
        instance()->log(msg);
}

void ZeeAdaptor::logWarning(QString msg){
    if(instance())
        instance()->logWarning(msg);
}

void ZeeAdaptor::logError(QString msg){
    if(instance())
        instance()->logError(msg);
}

void ZeeAdaptor::logCritical(QString msg){
    if(instance())
        instance()->logCritical(msg);
}

void ZeeAdaptor::logDebug(QString msg){
    if(instance())
        instance()->logDebug(msg);
}
