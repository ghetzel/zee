#include "zcmcoremodule.h"

ZCMCoreModule::ZCMCoreModule(){}

ZcmResult ZCMCoreModule::prepare(const QDomElement &el){
    ZcmResult rv = {NULL};

    if(0){
#ifdef ZEE_SETTING
    }else if(el.tagName() == ZEE_SETTING){
        rv.component = new ZSetting(el,qApp);
#endif // ZEE_SETTING
#ifdef ZEE_TIMER
    }else if(el.tagName() == ZEE_TIMER){
        rv.component = new ZTimer(el,qApp);
#endif // ZEE_TIMER
#ifdef ZEE_SYSTEM_INFO
    }else if(el.tagName() == ZEE_SYSTEM_INFO){
        rv.component = new ZSystemInfo(el,qApp);
#endif // ZEE_SYSTEM_INFO
    }

    return rv;
}

Q_EXPORT_PLUGIN2(zcm_core, ZCMCoreModule)
