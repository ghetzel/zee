#ifndef ZSYSTEMINFO_H
#define ZSYSTEMINFO_H
#define ZEE_SYSTEM_INFO         "zee:system"
#define ZSYS_NOTIFY_DURATION    5000
#define ZSYS_FTIME_DEFAULT_FMT  "ddd, d-MMM yyyy - h:mm:ssAP"

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
    Q_PROPERTY(QString ftime READ ftime)
public:
    ZSystemInfo(const ZConfig &el, QObject *parent=0);
    void parse(const ZConfig&);
    qint64 time();
    qint64 timems();
    QString ftime();

public slots:
    void notify(QString title, QString message=QString(),
                QString icon=QString(), int duration=ZSYS_NOTIFY_DURATION);

private:
    ZLocalSystem *_sysinfo;
    QString _dateTimeFormat;
};

#endif // ZSYSTEMINFO_H
