#include "zcpuinfo.h"

ZCPUInfo::ZCPUInfo(sigar_t *s, QObject *parent)
    : ZSigarModule(s, parent)
{
    init();
    setObjectName(ZSYS_INFO_CPU);
}

void ZCPUInfo::init(){
    if(_sigar){
        sigar_cpu_list_get(_sigar, &_s_cpu);
        sigar_cpu_info_list_get(_sigar, &_s_cpu_info);

        for(int i = 0; i < _s_cpu.size; i++){
            _lastCpuIdle << _s_cpu.data[i].idle;
            _lastCpuNice << _s_cpu.data[i].nice;
            _lastCpuSys << _s_cpu.data[i].sys;
            _lastCpuUser << _s_cpu.data[i].user;
            _lastCpuWait << _s_cpu.data[i].wait;
            _lastCpuSteal << _s_cpu.data[i].stolen;
            _lastCpuIRQ << _s_cpu.data[i].irq;
            _lastCpuSIRQ << _s_cpu.data[i].soft_irq;
        }

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

        if(_s_cpu.size == _s_cpu_info.size){
            setProperty("count", CAST(quint64,_s_cpu.number));
            setProperty("vendor", QVariant(_s_cpu_info.data[0].vendor));
            setProperty("model", QVariant(_s_cpu_info.data[0].model));

            for(int i = 0; i < _s_cpu.size; i++){
                qint64 d_idle =     CAST(quint64,_s_cpu.data[i].idle)-_lastCpuIdle[i];
                qint64 d_nice =     CAST(quint64,_s_cpu.data[i].nice)-_lastCpuNice[i];
                qint64 d_sys =      CAST(quint64,_s_cpu.data[i].sys)-_lastCpuSys[i];
                qint64 d_user =     CAST(quint64,_s_cpu.data[i].user)-_lastCpuUser[i];
                qint64 d_wait =     CAST(quint64,_s_cpu.data[i].wait)-_lastCpuWait[i];
                qint64 d_irq =      CAST(quint64,_s_cpu.data[i].irq)-_lastCpuIRQ[i];
                qint64 d_sirq =     CAST(quint64,_s_cpu.data[i].soft_irq)-_lastCpuSIRQ[i];
                qint64 d_steal =    CAST(quint64,_s_cpu.data[i].stolen)-_lastCpuSteal[i];

                qint64 d_active =   d_nice + d_sys + d_user + d_irq + d_sirq + d_steal;
                qint64 d_total =    d_active + d_idle + d_wait;

                QObject *proc = _processors[i];

                proc->setProperty("idle",           (CAST(double,d_idle)/CAST(double,d_total))*100.0);
                proc->setProperty("irq",            (CAST(double,d_irq)/CAST(double,d_total))*100.0);
                proc->setProperty("nice",           (CAST(double,d_nice)/CAST(double,d_total))*100.0);
                proc->setProperty("soft_irq",       (CAST(double,d_sirq)/CAST(double,d_total))*100.0);
                proc->setProperty("stolen",         (CAST(double,d_steal)/CAST(double,d_total))*100.0);
                proc->setProperty("system",         (CAST(double,d_sys)/CAST(double,d_total))*100.0);
                proc->setProperty("total",          (CAST(double,d_active)/CAST(double,d_total))*100.0);
                proc->setProperty("user",           (CAST(double,d_user)/CAST(double,d_total))*100.0);
                proc->setProperty("wait",           (CAST(double,d_wait)/CAST(double,d_total))*100.0);

                _lastCpuIdle[i] =   CAST(quint64,_s_cpu.data[i].idle);
                _lastCpuNice[i] =   CAST(quint64,_s_cpu.data[i].nice);
                _lastCpuSys[i] =    CAST(quint64,_s_cpu.data[i].sys);
                _lastCpuUser[i] =   CAST(quint64,_s_cpu.data[i].user);
                _lastCpuWait[i] =   CAST(quint64,_s_cpu.data[i].wait);
                _lastCpuSteal[i] =  CAST(quint64,_s_cpu.data[i].stolen);
                _lastCpuIRQ[i] =    CAST(quint64,_s_cpu.data[i].irq);
                _lastCpuSIRQ[i] =   CAST(quint64,_s_cpu.data[i].soft_irq);
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
