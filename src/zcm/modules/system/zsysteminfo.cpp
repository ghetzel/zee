#include "zsysteminfo.h"

ZSystemInfo::ZSystemInfo(QObject *parent)
    : QObject(parent)
{
    setObjectName(ZSYS_INFO);
}


void ZSystemInfo::init(){
#ifdef ZDISKINFO_H
    _info << new ZDiskInfo(this);
#endif
#ifdef ZCPUINFO_H
    _info << new ZCPUInfo(this);
#endif
#ifdef ZHARDWAREINFO_H
    _info << new ZHardwareInfo(this);
#endif
#ifdef ZMEMORYINFO_H
    _info << new ZMemoryInfo(this);
#endif
#ifdef ZNETWORKINFO_H
    _info << new ZNetworkInfo(this);
#endif
}
