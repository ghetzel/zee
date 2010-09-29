#include "zhardwareinfo.h"

ZHardwareInfo::ZHardwareInfo(QObject *parent)
    : QObject(parent)
{
    setObjectName(ZSYS_INFO_HARDWARE);
}
