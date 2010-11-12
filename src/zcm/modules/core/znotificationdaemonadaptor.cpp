#include "znotificationdaemonadaptor.h"

ZNotificationDaemonAdaptor::ZNotificationDaemonAdaptor(ZNotificationDaemon *parent)
    : ZDBusAbstractAdaptor(ZNOTIFY_GALAGO_SERVICE_NAME,
                           ZNOTIFY_GALAGO_OBJECT_PATH, parent)
{
    init();
}

void ZNotificationDaemonAdaptor::init(){
    if(instance()){
    //  connect local signals to instance signals
    }

    registerService();
}

ZNotificationDaemon *ZNotificationDaemonAdaptor::instance(){
    return QCAST(ZNotificationDaemon*,ZDBusAbstractAdaptor::instance());
}


uint ZNotificationDaemonAdaptor::Notify(QString appName, uint id, QString icon,
                                        QString summary, QString body,
                                        QStringList actions,
                                        QVariantMap hints,
                                        int timeout)
{
    if(instance()){
        return instance()->Notify(appName, id, icon, summary, body,
                                  actions, hints, timeout);
    }

    return -1;
}
