#include "zmemoryinfo.h"

ZMemoryInfo::ZMemoryInfo(QObject *parent)
    : QObject(parent)
{
    setObjectName(ZSYS_INFO_MEMORY);
}
