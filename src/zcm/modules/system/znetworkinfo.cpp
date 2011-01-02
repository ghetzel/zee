#include "znetworkinfo.h"

ZNetworkInfo::ZNetworkInfo(sigar_t *s, QObject *parent)
    : ZSigarModule(s, parent)
{
    if(s)
        init();

    setObjectName(ZSYS_INFO_NETWORK);
}

void ZNetworkInfo::init(){
    sigar_net_interface_list_t interfaces;
    sigar_net_interface_list_get(_sigar, &interfaces);

    for(int i = 0; i < interfaces.number; i++){
        _interfaces.append(new ZNetInterfaceInfo(QString(interfaces.data[i]),
                                                 _sigar, this));
    }

    sigar_net_interface_list_destroy(_sigar, &interfaces);
}

void ZNetworkInfo::refresh(){
    if(_sigar){
        sigar_net_info_get(_sigar, &_s_net_info);

        setProperty("hostname",     QVariant(_s_net_info.host_name));
        setProperty("domain",       QVariant(_s_net_info.domain_name));
        setProperty("gateway",      QVariant(_s_net_info.default_gateway));
        setProperty("dns1",         QVariant(_s_net_info.primary_dns));
        setProperty("dns2",         QVariant(_s_net_info.secondary_dns));


        foreach(ZNetInterfaceInfo *interface, _interfaces){
            interface->refresh();
        }

        emit refreshed();
    }
}
