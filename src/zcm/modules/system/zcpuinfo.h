#ifndef ZCPUINFO_H
#define ZCPUINFO_H

#define ZSYS_INFO_CPU           "cpu"

#include <QObject>

class ZCPUInfo : public QObject
{
public:
    ZCPUInfo(QObject *parent=0);
};

#endif // ZCPUINFO_H
