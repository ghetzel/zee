#ifndef ZNOTIFICATIONDAEMON_H
#define ZNOTIFICATIONDAEMON_H

#define ZCM_NOTIFICATION_DAEMON         "zee:notify-daemon"

#include <QStringList>
#include <QVariantMap>
#include <zconfigurable.h>
#include <zeventmanager.h>

class ZNotificationDaemonAdaptor;

class ZNotificationDaemon : public QObject, public ZConfigurable
{
    Q_OBJECT

public:
    ZNotificationDaemon(const ZConfig &el, QObject *parent=0);
    void setAdaptor(ZNotificationDaemonAdaptor *adaptor);

public slots:
    uint Notify(QString appName, uint id, QString icon, QString summary,
                QString body, QStringList actions,
                QVariantMap hints, int timeout);

signals:
    void received(QString body);
    void received(QString body, QString title);
    void received(QString body, QString title, QString icon);
    void received(QString body, QString title, QString icon, int timeout);

private:
    void parse(const ZConfig &el);

private:
    ZNotificationDaemonAdaptor *_adaptor;
};

#endif // ZNOTIFICATIONDAEMON_H
