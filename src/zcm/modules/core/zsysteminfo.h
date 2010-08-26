#ifndef ZSYSTEMINFO_H
#define ZSYSTEMINFO_H
#define ZEE_SYSTEM_INFO        "zee:system"
#define ZSYS_NOTIFY_DURATION   5000

#include <iostream>
#include <QObject>
#include <libzee/zlocalsystem.h>
#include <zconfigurable.h>
#include <zeventmanager.h>
#ifdef Q_OS_LINUX
#define ZSYS_LNOTIFY_SVCNM  "org.freedesktop.Notifications"
#define ZSYS_LNOTIFY_OPATH  "/org/freedesktop/Notifications"
#define ZSYS_LNOTIFY_IFACE  "org.freedesktop.Notifications"
#define ZSYS_LNOTIFY_METHOD "Notify"
#include <QtDBus>
#endif

class ZSystemInfo : public QObject, public ZConfigurable
{
    Q_OBJECT
    Q_PROPERTY(qint64 time READ time)
    Q_PROPERTY(qint64 timems READ timems)
public:
    ZSystemInfo(const ZConfig &el, QObject *parent=0);
    void parse(const ZConfig&);
    qint64 time();
    qint64 timems();

public slots:
    void notify(QString title, QString message=QString(),
                QString icon=QString(), int duration=ZSYS_NOTIFY_DURATION);

private:
    ZLocalSystem *_sysinfo;
};

#endif // ZSYSTEMINFO_H
