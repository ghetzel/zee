/******************************************************************************
*    This file is part of Zee.
*
*    Zee is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    Zee is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with Zee.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

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
