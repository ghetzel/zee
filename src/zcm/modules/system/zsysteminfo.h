#ifndef ZSYSTEMINFO_H
#define ZSYSTEMINFO_H

#include <QObject>
#include <zeventmanager.h>
#include <zconfigurable.h>

class ZSystemInfo : public QObject, public ZConfigurable
{
public:
    ZSystemInfo(const ZConfig &el, QObject *parent=0);
};

#endif // ZSYSTEMINFO_H
