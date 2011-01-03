#ifndef ZDISKINFO_H
#define ZDISKINFO_H

#define ZSYS_INFO_DISK          "disk"

#include <QObject>
#include <QHash>
#include <libzee.h>
#include <zsigarmodule.h>

class ZDiskInfo : public ZSigarModule
{
    Q_OBJECT
public:
    ZDiskInfo(sigar_t *s, QObject *parent=0);

public slots:
    virtual void refresh();

private:
    void init();
    void refreshFilesystems();

private:
    QHash<QString,QObject*> _filesystems;
};

#endif // ZDISKINFO_H
