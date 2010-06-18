#include "zsysteminfo.h"

ZSystemInfo::ZSystemInfo(const ZConfig &el, QObject *parent)
    : QObject(parent),
      ZConfigurable(el,this)
{
    _sysinfo = ZLocalSystem::instance();
    parse(_config);
}

void ZSystemInfo::parse(const ZConfig &el){

    zEvent->registerSlot(this, SLOT(notify(QString)));
    zEvent->registerSlot(this, SLOT(notify(QString,QString)));
    zEvent->registerSlot(this, SLOT(notify(QString,QString,QString)));
    zEvent->registerSlot(this, SLOT(notify(QString,QString,QString,uint)));
}

qint64 ZSystemInfo::time(){
    return CAST(qint64,_sysinfo->systemTime().toTime_t());
}

qint64 ZSystemInfo::timems(){
    return _sysinfo->systemTimeEpoch();
}

void ZSystemInfo::notify(QString title, QString message, QString icon,
                         uint duration)
{
#ifdef Q_OS_LINUX
    QDBusInterface i(ZSYS_LNOTIFY_SVCNM,ZSYS_LNOTIFY_OPATH,ZSYS_LNOTIFY_IFACE);
    i.call("Notify",ZEE_APPNAME,uint(0),icon,title,message,QStringList(),
           QVariantMap(),duration);
#endif
}
