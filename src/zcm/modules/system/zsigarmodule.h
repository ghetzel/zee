#ifndef ZSIGARMODULE_H
#define ZSIGARMODULE_H

#include <QObject>
#include <sigar.h>
#include <zutil.h>
#include <zeventmanager.h>

class ZSigarModule : public QObject
{
    Q_OBJECT
public:
    ZSigarModule(sigar_t *s, QObject *parent=0)
        : QObject(parent){
        _sigar = s;

        zEvent->registerSignal(this, SIGNAL(refreshed()));
        zEvent->registerSlot(this, SLOT(refresh()));
    }

signals:
    void refreshed();

public slots:
    virtual void refresh()=0;

protected:
    sigar_t *_sigar;
};

#endif // ZSIGARMODULE_H
