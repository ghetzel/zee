#ifndef ZNETWORKINFO_H
#define ZNETWORKINFO_H

#define ZSYS_INFO_NETWORK       "net"

#include <QObject>

class ZNetworkInfo : public QObject
{
public:
    ZNetworkInfo(QObject *parent=0);
};

#endif // ZNETWORKINFO_H
