#include "zsysteminfo.h"

ZSystemInfo::ZSystemInfo(const ZConfig &el, QObject *parent)
    : QObject(parent),
      ZConfigurable(el,this)
{
    init();
}

void ZSystemInfo::init(){
    zEvent->registerSignal(this, SIGNAL(refreshed()));
    zEvent->registerSlot(this, SLOT(refresh()));

    sigar_open(&_sigar);

    if(_sigar){
        _modules << new ZCPUInfo(_sigar, this);
    }
}

void ZSystemInfo::parse(const ZConfig &el){
}

void ZSystemInfo::refresh(){
    foreach(ZSigarModule *module, _modules){
        module->refresh();
    }
}
