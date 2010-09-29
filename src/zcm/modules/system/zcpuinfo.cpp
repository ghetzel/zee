#include "zcpuinfo.h"

ZCPUInfo::ZCPUInfo(QObject *parent)
    : QObject(parent)
{
    setObjectName(ZSYS_INFO_CPU);
}
