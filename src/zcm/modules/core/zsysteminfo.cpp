#include "zsysteminfo.h"

ZSystemInfo::ZSystemInfo(const ZConfig &el, QObject *parent)
    : QObject(parent),
      ZConfigurable(el,this)
{
    _sysinfo = ZLocalSystem::instance();
    _dateTimeFormat = ZSYS_FTIME_DEFAULT_FMT;

    zEvent->registerSlot(this, SLOT(notify(QString)));
    zEvent->registerSlot(this, SLOT(notify(QString,QString)));
    zEvent->registerSlot(this, SLOT(notify(QString,QString,QString)));
    zEvent->registerSlot(this, SLOT(notify(QString,QString,QString,int)));

    parse(_config);
}

void ZSystemInfo::parse(const ZConfig&){
    if(param("timeFormat").isValid())
        _dateTimeFormat = param("timeFormat").toString();

}

qint64 ZSystemInfo::time(){
    return CAST(qint64,_sysinfo->systemTime().toTime_t());
}

qint64 ZSystemInfo::timems(){
    return _sysinfo->systemTimeEpoch();
}

QString ZSystemInfo::ftime(){
    return _sysinfo->systemTime().toString(_dateTimeFormat);
}

void ZSystemInfo::notify(QString title, QString message, QString icon,
                         int duration)
{
#ifdef Q_OS_LINUX
    QDBusInterface i(ZSYS_LNOTIFY_SVCNM,ZSYS_LNOTIFY_OPATH,ZSYS_LNOTIFY_IFACE);
    QDBusMessage res;
    res = i.call(ZSYS_LNOTIFY_METHOD,ZEE_APPNAME,uint(0),icon,title,message,QStringList(),
	   QVariantMap(),duration);
#else
    z_log("ZSystemInfo: Notification support is not currently implemented for your platform.");
#endif
}
