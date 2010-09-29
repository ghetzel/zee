/******************************************************************************
*    This file is part of Zee.
*
*    Zee is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    Zee is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with Zee.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#include "zsysteminfo.h"

ZSystemInfo::ZSystemInfo(const ZConfig &el, QObject *parent)
    : QObject(parent),
      ZConfigurable(el,this)
{
    _sysinfo = ZLocalSystem::instance();
    _dateTimeFormat = ZSYS_FTIME_DEFAULT_FMT;

    zEvent->registerSlot(this, SLOT(notify(QString)));
    zEvent->registerSlot(this, SLOT(notify(QString,QString)));
    zEvent->registerSlot(this, SLOT(notify(QString,QString,QString)));
    zEvent->registerSlot(this, SLOT(notify(QString,QString,QString,int)));

    parse(_config);
}

void ZSystemInfo::parse(const ZConfig&){
    if(param("timeFormat").isValid())
	_dateTimeFormat = param("timeFormat").toString();

    sigar_t *info = NULL;

    sigar_open(&info);


    if(info){
        sigar_cpu_list_t cpu;
        sigar_cpu_list_get(info, &cpu);

        sigar_mem_t mem;
        sigar_mem_get(info, &mem);

        sigar_net_interface_list_t netif;
        sigar_net_interface_list_get(info, &netif);



        sigar_uptime_t uptime;
        sigar_uptime_get(info, &uptime);

        sigar_loadavg_t load;
        sigar_loadavg_get(info, &load);

        sigar_cpu_info_list_t cpuinfo;
        sigar_cpu_info_list_get(info, &cpuinfo);

        sigar_net_info_t netinfo;
        sigar_net_info_get(info, &netinfo);

        sigar_file_system_list_t fslist;
        sigar_file_system_list_get(info, &fslist);

        sigar_net_address_t na;
        sigar_net_connection_t nc;
        sigar_net_interface_stat_t nifs;

        sigar_sys_info_t sys;
        sigar_sys_info_get(info, &sys);


        qDebug() << "ZSystemInfo: SYSMACH " << sys.machine;
        qDebug() << "ZSystemInfo: SYSARCH " << sys.arch;
        qDebug() << "ZSystemInfo: SYSDESC " << sys.description;
        qDebug() << "ZSystemInfo: SYSNAME " << sys.name;
        qDebug() << "ZSystemInfo: PATCHLV " << sys.patch_level;
        qDebug() << "ZSystemInfo: VERSION " << sys.version;
        qDebug() << "ZSystemInfo: VENDOR  " << sys.vendor;
        qDebug() << "ZSystemInfo: VENDCNM " << sys.vendor_code_name;
        qDebug() << "ZSystemInfo: VENDNAM " << sys.vendor_name;
        qDebug() << "ZSystemInfo: VENDVER " << sys.vendor_version;

        qDebug() << "ZSystemInfo: HOST " << netinfo.host_name << "." << netinfo.domain_name;
        qDebug() << "ZSystemInfo: GW " << netinfo.default_gateway;
        qDebug() << "ZSystemInfo: DNS1 " << netinfo.primary_dns;
        qDebug() << "ZSystemInfo: DNS2 " << netinfo.secondary_dns;

        qDebug() << "ZSystemInfo: CPU " << cpu.number;
        for(int i = 0; i < cpuinfo.number; i++){
            qDebug() << "\tCLOCK"<< i << cpuinfo.data[i].mhz;
            qDebug() << "\tCACHE"<< i << cpuinfo.data[i].cache_size;
            qDebug() << "\tCRSCK"<< i << cpuinfo.data[i].cores_per_socket;
            qDebug() << "\tCORES"<< i << cpuinfo.data[i].total_cores;
            qDebug() << "\tSOCKS"<< i << cpuinfo.data[i].total_sockets;
            qDebug() << "\tVENDR"<< i << cpuinfo.data[i].vendor;
            qDebug() << "\tMODEL"<< i << cpuinfo.data[i].model;



        }

        qDebug() << "ZSystemInfo: RAM " << mem.used_percent;
        qDebug() << "ZSystemInfo: UPTIME " << uptime.uptime;
        qDebug() << "ZSystemInfo: LOAD 1 =" << load.loadavg[0] << " 5 =" << load.loadavg[1] << " 15 =" << load.loadavg[2];

        qDebug() << "ZSystemInfo: FS " << fslist.number;
        for(int i = 0; i < fslist.number; i++){
            qDebug() << "DEV"<< fslist.data[i].dev_name;
            qDebug() << "\tDIR"<< fslist.data[i].dir_name;
            qDebug() << "\tTYPE" << fslist.data[i].type_name << " ("<<fslist.data[i].type<<")";
            qDebug() << "\tFLAG"<< i << fslist.data[i].flags;
            qDebug() << "\tOPTS"<< i << fslist.data[i].options;
            qDebug() << "\tSYSTYP"<< i << fslist.data[i].sys_type_name;
            qDebug() << "";
        }
  }
}

qint64 ZSystemInfo::time(){
    return ZDateTime::now_t();
}

qint64 ZSystemInfo::timeMsec(){
    return ZDateTime::nowMsec_t();
}

void ZSystemInfo::notify(QString title, QString message, QString icon,
			 int duration)
{
#ifdef Q_OS_LINUX
    QDBusInterface i(ZSYS_LNOTIFY_SVCNM,ZSYS_LNOTIFY_OPATH,ZSYS_LNOTIFY_IFACE);
    QDBusMessage res;
    res = i.call(ZSYS_LNOTIFY_METHOD,ZEE_APPNAME,uint(0),icon,title,message,QStringList(),
	   QVariantMap(),duration);
#else
    z_log("ZSystemInfo: Notification support is not currently implemented for your platform.");
#endif
}
