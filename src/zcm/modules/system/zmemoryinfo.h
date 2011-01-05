#ifndef ZMEMORYINFO_H
#define ZMEMORYINFO_H

#define ZSYS_INFO_MEMORY        "mem"
#define ZSYS_INFO_MEMORY_SWAP   "swap"

#include <zsigarmodule.h>

class ZMemoryInfo : public ZSigarModule
{
    Q_OBJECT
public:
    ZMemoryInfo(sigar_t *s, QObject *parent=0);

public slots:
    virtual void refresh();

private:
    void init();

private:
    QObject *_swap;
};

#endif // ZMEMORYINFO_H
