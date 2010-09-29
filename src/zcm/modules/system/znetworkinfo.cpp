#include "znetworkinfo.h"

ZNetworkInfo::ZNetworkInfo(QObject *parent)
    : QObject(parent)
{
    setObjectName(ZSYS_INFO_NETWORK);
}
