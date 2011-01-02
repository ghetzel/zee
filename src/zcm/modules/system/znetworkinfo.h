#ifndef ZNETWORKINFO_H
#define ZNETWORKINFO_H

#define ZSYS_INFO_NETWORK       "net"

#include <QObject>
#include <zsigarmodule.h>
#include <znetinterfaceinfo.h>

class ZNetworkInfo : public ZSigarModule
{
    Q_OBJECT
public:
    ZNetworkInfo(sigar_t *s, QObject *parent=0);

public slots:
    virtual void refresh();

private:
    void init();

private:
    sigar_net_info_t _s_net_info;
    QList<ZNetInterfaceInfo*> _interfaces;
};

#endif // ZNETWORKINFO_H
