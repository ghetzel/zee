#ifndef ZNOTIFICATIONDAEMONADAPTOR_H
#define ZNOTIFICATIONDAEMONADAPTOR_H

#define ZNOTIFY_GALAGO_SERVICE_NAME     "org.freedesktop.Notifications"
#define ZNOTIFY_GALAGO_OBJECT_PATH      "org/freedesktop/Notifications"
#define ZNOTIFY_GALAGO_INTERFACE        "org.freedesktop.Notifications"

#include <QObject>
#include <QDBusVariant>
#include <znotificationdaemon.h>
#include <zdbusabstractadaptor.h>

class ZNotificationDaemonAdaptor : public ZDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.freedesktop.Notifications")

public:
    ZNotificationDaemonAdaptor(ZNotificationDaemon *parent);

public slots:
    uint Notify(QString appName, uint id, QString icon, QString summary,
                QString body, QStringList actions,
                QVariantMap hints, int timeout);

private:
    void init();
    ZNotificationDaemon *instance();
};

#endif // ZNOTIFICATIONDAEMONADAPTOR_H
