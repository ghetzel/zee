#ifndef ZMEMORYINFO_H
#define ZMEMORYINFO_H

#define ZSYS_INFO_MEMORY        "mem"

#include <QObject>

class ZMemoryInfo : public QObject
{
public:
    ZMemoryInfo(QObject *parent=0);
};

#endif // ZMEMORYINFO_H
