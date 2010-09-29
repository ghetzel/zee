#ifndef ZHARDWAREINFO_H
#define ZHARDWAREINFO_H

#define ZSYS_INFO_HARDWARE      "hw"

#include <QObject>

class ZHardwareInfo : public QObject
{
public:
    ZHardwareInfo(QObject *parent=0);
};

#endif // ZHARDWAREINFO_H
