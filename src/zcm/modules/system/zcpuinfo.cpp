#include "zcpuinfo.h"

ZCPUInfo::ZCPUInfo(sigar_t *s, QObject *parent)
    : ZSigarModule(s, parent)
{
    init();
    setObjectName(ZSYS_INFO_CPU);
}

void ZCPUInfo::init(){
    if(_sigar){
        sigar_cpu_info_list_get(_sigar, &_s_cpu_info);

        for(int i = 0; i < _s_cpu_info.size; i++){
            QString label = "cpu"+STR(i);
            QObject *proc = new QObject(this);
            proc->setObjectName(label);

            _processors << proc;
        }
    }
}

void ZCPUInfo::refresh(){
    if(_sigar){
        sigar_cpu_list_get(_sigar, &_s_cpu);
        sigar_cpu_info_list_get(_sigar, &_s_cpu_info);

        if(_s_cpu.number == _s_cpu_info.number){
            setProperty("count", CAST(quint64,_s_cpu.number));
            setProperty("vendor", QVariant(_s_cpu_info.data[0].vendor));
            setProperty("model", QVariant(_s_cpu_info.data[0].model));

            for(int i = 0; i < _s_cpu.size; i++){
                QObject *proc = _processors[i];

                proc->setProperty("idle",           CAST(quint64,_s_cpu.data[i].idle));
                proc->setProperty("irq",            CAST(quint64,_s_cpu.data[i].irq));
                proc->setProperty("nice",           CAST(quint64,_s_cpu.data[i].nice));
                proc->setProperty("soft_irq",       CAST(quint64,_s_cpu.data[i].soft_irq));
                proc->setProperty("stolen",         CAST(quint64,_s_cpu.data[i].stolen));
                proc->setProperty("system",         CAST(quint64,_s_cpu.data[i].sys));
                proc->setProperty("total",          CAST(quint64,_s_cpu.data[i].total));
                proc->setProperty("user",           CAST(quint64,_s_cpu.data[i].user));
                proc->setProperty("wait",           CAST(quint64,_s_cpu.data[i].wait));
            }

            for(int i = 0; i < _s_cpu_info.size; i++){
                QObject *proc = _processors[i];

                proc->setProperty("clock",          CAST(quint64,_s_cpu_info.data[i].mhz));
                proc->setProperty("cores",          CAST(quint64,_s_cpu_info.data[i].total_cores));
                proc->setProperty("sockets",        CAST(quint64,_s_cpu_info.data[i].total_sockets));
                proc->setProperty("coresPerSocket", CAST(quint64,_s_cpu_info.data[i].cores_per_socket));
                proc->setProperty("cache",          CAST(quint64,_s_cpu_info.data[i].cache_size));
            }
        }

        sigar_cpu_list_destroy(_sigar, &_s_cpu);
        sigar_cpu_info_list_destroy(_sigar, &_s_cpu_info);

        emit refreshed();
    }
}
