#ifndef ZSYSTEMINFO_H
#define ZSYSTEMINFO_H

#define ZCM_SYSTEMINFO          "zee:system"

#include <QObject>
#include <zeventmanager.h>
#include <zconfigurable.h>

// info modules
#include <zcpuinfo.h>

class ZSystemInfo : public QObject, public ZConfigurable
{
    Q_OBJECT

public:
    ZSystemInfo(const ZConfig &el, QObject *parent=0);

signals:
    void refreshed();

public slots:
    void refresh();

private:
    void init();
    void parse(const ZConfig &el);

private:
    sigar_t *_sigar;
    QList<ZSigarModule*> _modules;
};

#endif // ZSYSTEMINFO_H
