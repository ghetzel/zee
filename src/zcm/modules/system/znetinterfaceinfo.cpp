#include "znetinterfaceinfo.h"

ZNetInterfaceInfo::ZNetInterfaceInfo(QString ifname, sigar_t *s, QObject *parent)
    : ZSigarModule(s,parent)
{
    _ifname = CSTR(ifname);
    init();
    setObjectName(ifname);
}

void ZNetInterfaceInfo::init(){
    refresh();
}

void ZNetInterfaceInfo::refresh(){
    sigar_net_interface_stat_t netif_stat;
    sigar_net_interface_config_t netif_config;

    sigar_net_interface_stat_get(_sigar, _ifname, &netif_stat);
    sigar_net_interface_config_get(_sigar, _ifname, &netif_config);

//  because MAC addresses are *sooo effin special*...
    char hwaddr[18];
    sprintf(hwaddr, "%02X:%02X:%02X:%02X:%02X:%02X",
        netif_config.hwaddr.addr.mac[0],
        netif_config.hwaddr.addr.mac[1],
        netif_config.hwaddr.addr.mac[2],
        netif_config.hwaddr.addr.mac[3],
        netif_config.hwaddr.addr.mac[4],
        netif_config.hwaddr.addr.mac[5]);

//  config
    setProperty("ipaddress",    IP4RDECTOSTR(CAST(quint32,netif_config.address.addr.in)));
    setProperty("netmask",      IP4RDECTOSTR(CAST(quint32,netif_config.netmask.addr.in)));
    setProperty("broadcast",    IP4RDECTOSTR(CAST(quint32,netif_config.broadcast.addr.in)));
    setProperty("destination",  IP4RDECTOSTR(CAST(quint32,netif_config.destination.addr.in)));
    setProperty("description",  QVariant(netif_config.description));
    setProperty("flags",        QVariant(CAST(quint64,netif_config.flags)));
    setProperty("hwaddr",       QVariant(CAST(const char*,hwaddr)));
    setProperty("metric",       QVariant(CAST(quint64,netif_config.metric)));
    setProperty("mtu",          QVariant(CAST(quint64,netif_config.mtu)));
    setProperty("name",         QVariant(netif_config.name));
    setProperty("type",         QVariant(netif_config.type));

//  stats
    setProperty("linkSpeed",    QVariant(CAST(quint64,netif_stat.speed)));
    setProperty("rxBytes",      QVariant(CAST(quint64,netif_stat.rx_bytes)));
    setProperty("rxDropped",    QVariant(CAST(quint64,netif_stat.rx_dropped)));
    setProperty("rxErrors",     QVariant(CAST(quint64,netif_stat.rx_errors)));
    setProperty("rxFrames",     QVariant(CAST(quint64,netif_stat.rx_frame)));
    setProperty("rxOverruns",   QVariant(CAST(quint64,netif_stat.rx_overruns)));
    setProperty("rxPackets",    QVariant(CAST(quint64,netif_stat.rx_packets)));
    setProperty("txBytes",      QVariant(CAST(quint64,netif_stat.tx_bytes)));
    setProperty("txCarrier",    QVariant(CAST(quint64,netif_stat.tx_carrier)));
    setProperty("txCollisions", QVariant(CAST(quint64,netif_stat.tx_collisions)));
    setProperty("txDropped",    QVariant(CAST(quint64,netif_stat.tx_dropped)));
    setProperty("txErrors",     QVariant(CAST(quint64,netif_stat.tx_errors)));
    setProperty("txOverruns",   QVariant(CAST(quint64,netif_stat.tx_overruns)));
    setProperty("txPackets",    QVariant(CAST(quint64,netif_stat.tx_packets)));
}
