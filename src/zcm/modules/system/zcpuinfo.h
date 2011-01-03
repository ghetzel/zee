#ifndef ZCPUINFO_H
#define ZCPUINFO_H

#define ZSYS_INFO_CPU           "cpu"

#include <QObject>
#include <QHash>
#include <zutil.h>
#include <zsigarmodule.h>

class ZCPUInfo : public ZSigarModule
{
    Q_OBJECT
public:
    ZCPUInfo(sigar_t *s, QObject *parent=0);

public slots:
    virtual void refresh();

private:
    void init();

private:
    sigar_cpu_list_t _s_cpu;
    sigar_cpu_info_list_t _s_cpu_info;
    QList<QObject*> _processors;
    QList<qint64> _lastCpuUser;
    QList<qint64> _lastCpuSys;
    QList<qint64> _lastCpuNice;
    QList<qint64> _lastCpuIdle;
    QList<qint64> _lastCpuTotal;
    QList<qint64> _lastCpuWait;
    QList<qint64> _lastCpuSteal;
    QList<qint64> _lastCpuIRQ;
    QList<qint64> _lastCpuSIRQ;
};

#endif // ZCPUINFO_H
