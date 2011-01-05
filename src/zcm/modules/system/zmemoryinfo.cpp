#include "zmemoryinfo.h"

ZMemoryInfo::ZMemoryInfo(sigar_t *s, QObject *parent)
    : ZSigarModule(s,parent)
{
    setObjectName(ZSYS_INFO_MEMORY);
    init();
}

void ZMemoryInfo::init(){
    _swap = new QObject(this);
    _swap->setObjectName(ZSYS_INFO_MEMORY_SWAP);
    refresh();
}

void ZMemoryInfo::refresh(){
    if(_sigar){
        sigar_swap_t swap;
        sigar_mem_t memory;
        sigar_mem_get(_sigar, &memory);
        sigar_swap_get(_sigar, &swap);

        setProperty("freeMB",           QVariant(CAST(quint64,memory.actual_free)));
        setProperty("usedMB",           QVariant(CAST(quint64,memory.actual_used)));
        //setProperty("free",     QVariant(CAST(quint64,memory.free)));
        //setProperty("used",     QVariant(CAST(quint64,memory.used)));
        setProperty("ram",              QVariant(CAST(quint64,memory.ram)));
        setProperty("totalMB",          QVariant(CAST(quint64,memory.total)));
        setProperty("free",             QVariant(CAST(qreal,memory.free_percent)));
        setProperty("used",             QVariant(CAST(qreal,memory.used_percent)));

        qreal swapFreePerc = (CAST(qreal,swap.free)/CAST(qreal,swap.total))*100.0;
        qreal swapUsedPerc = (CAST(qreal,swap.used)/CAST(qreal,swap.total))*100.0;

        _swap->setProperty("free",      QVariant(swapFreePerc));
        _swap->setProperty("used",      QVariant(swapUsedPerc));
        _swap->setProperty("freeMB",    QVariant(CAST(quint64,swap.free)));
        _swap->setProperty("pagesIn",   QVariant(CAST(quint64,swap.page_in)));
        _swap->setProperty("pagesOut",  QVariant(CAST(quint64,swap.page_out)));
        _swap->setProperty("totalMB",   QVariant(CAST(quint64,swap.total)));
        _swap->setProperty("usedMB",    QVariant(CAST(quint64,swap.used)));
    }
}
