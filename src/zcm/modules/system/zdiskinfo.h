#ifndef ZDISKINFO_H
#define ZDISKINFO_H

#define ZSYS_INFO_DISK          "disk"

#include <QObject>

class ZDiskInfo : public QObject
{
public:
    ZDiskInfo(QObject *parent=0);
};

#endif // ZDISKINFO_H
