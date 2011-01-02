#ifndef ZNETINTERFACEINFO_H
#define ZNETINTERFACEINFO_H


#include <QObject>
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
    const char *_ifname;
};

#endif // ZNETINTERFACEINFO_H
