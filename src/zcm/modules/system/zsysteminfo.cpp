#include "zsysteminfo.h"

ZSystemInfo::ZSystemInfo(const ZConfig &el, QObject *parent)
    : QObject(parent),
      ZConfigurable(el,this)
{
    init();
}

ZSystemInfo::~ZSystemInfo(){
    sigar_close(_sigar);
}

void ZSystemInfo::init(){
    sigar_open(&_sigar);

    if(_sigar){
        _modules << new ZCPUInfo(_sigar, this);
        _modules << new ZDiskInfo(_sigar, this);
        _modules << new ZNetworkInfo(_sigar, this);
    }

    zEvent->registerSignal(this, SIGNAL(refreshed()));
    zEvent->registerSlot(this, SLOT(refresh()));

    foreach(ZSigarModule *module, _modules){
        zEvent->registerSignal(module, SIGNAL(refreshed()));
        zEvent->registerSlot(module, SLOT(refresh()));
    }
}

void ZSystemInfo::parse(const ZConfig &el){
}

void ZSystemInfo::refresh(){
    sigar_open(&_sigar);

    foreach(ZSigarModule *module, _modules){
        module->refresh();
    }

    sigar_close(_sigar);
}
