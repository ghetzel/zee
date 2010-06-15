#include "zsysteminfo.h"

ZSystemInfo::ZSystemInfo(const ZConfig &el, QObject *parent)
    : QObject(parent),
      ZConfigurable(el,this)
{
    _sysinfo = ZLocalSystem::instance();
    parse(_config);
}

void ZSystemInfo::parse(const ZConfig &el){
}

qint64 ZSystemInfo::time(){
    return CAST(qint64,_sysinfo->systemTime().toTime_t());
}

qint64 ZSystemInfo::timems(){
    return _sysinfo->systemTimeEpoch();
}
