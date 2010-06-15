#ifndef ZSYSTEMINFO_H
#define ZSYSTEMINFO_H
#define ZEE_SYSTEM_INFO        "zee:sysinfo"

#include <iostream>
#include <QObject>
#include <libzee/zlocalsystem.h>
#include <zconfigurable.h>
#include <zeventmanager.h>

class ZSystemInfo : public QObject, public ZConfigurable
{
    Q_OBJECT
    Q_PROPERTY(qint64 time READ time)
    Q_PROPERTY(qint64 timems READ timems)
public:
    ZSystemInfo(const ZConfig &el, QObject *parent=0);
    void parse(const ZConfig &el);
    qint64 time();
    qint64 timems();

private:
    ZLocalSystem *_sysinfo;
};

#endif // ZSYSTEMINFO_H
