#ifndef ZSYSTEMINFO_H
#define ZSYSTEMINFO_H

#include <QObject>
#include <sys/zdiskinfo.h>
#include <sys/zhardwareinfo.h>
#include <sys/zmemoryinfo.h>
#include <sys/znetworkinfo.h>
#include <sys/zcpuinfo.h>

class ZSystemInfo : public QObject
{
    Q_OBJECT
public:
    ZSystemInfo(QObject *parent=0);

private:
    void init();

private:
    QList<QObject*> _info;

};

#endif // ZSYSTEMINFO_H
