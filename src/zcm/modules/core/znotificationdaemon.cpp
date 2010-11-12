#include "znotificationdaemon.h"

ZNotificationDaemon::ZNotificationDaemon(const ZConfig &el, QObject *parent)
    : QObject(parent),
      ZConfigurable(el, this)
{
    zEvent->registerSignal(this, SIGNAL(received(QString)));
    zEvent->registerSignal(this, SIGNAL(received(QString,QString)));
    zEvent->registerSignal(this, SIGNAL(received(QString,QString,QString)));
    zEvent->registerSignal(this, SIGNAL(received(QString,QString,QString,int)));

    parse(_config);
}


void ZNotificationDaemon::parse(const ZConfig &el){
}


uint ZNotificationDaemon::Notify(QString appName, uint id, QString icon,
                                   QString summary, QString body,
                                   QStringList actions,
                                   QVariantMap hints,
                                   int timeout)
{
    emit received(body);
    emit received(body, summary);
    emit received(body, summary, icon);
    emit received(body, summary, icon, timeout);
}


void ZNotificationDaemon::setAdaptor(ZNotificationDaemonAdaptor *adaptor){
    _adaptor = adaptor;
}
