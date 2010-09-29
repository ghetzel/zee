#include "zdiskinfo.h"

ZDiskInfo::ZDiskInfo(QObject *parent)
    : QObject(parent)
{
    setObjectName(ZSYS_INFO_DISK);
}
