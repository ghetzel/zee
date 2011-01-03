#ifndef ZNETINTERFACEINFO_H
#define ZNETINTERFACEINFO_H


#include <QObject>
#include <libzee.h>
#include <zutil.h>
#include <zsigarmodule.h>

class ZNetInterfaceInfo :  public ZSigarModule
{
    Q_OBJECT
public:
    ZNetInterfaceInfo(QString ifname, sigar_t *s, QObject *parent=0);

public slots:
    virtual void refresh();

private:
    void init();

private:
    quint64 _lastCollectTime;
    quint64 _lastRxBits;
    quint64 _lastTxBits;
    const char *_ifname;
};

#endif // ZNETINTERFACEINFO_H
