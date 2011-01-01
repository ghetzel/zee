#include "zcmsystemmodule.h"

ZCMSystemModule::ZCMSystemModule(){}

ZcmResult ZCMSystemModule::prepare(const QDomElement &el){
    ZcmResult rv;

    if(0){
#ifdef ZCM_SYSTEMINFO
    }else if(el.tagName() == ZCM_SYSTEMINFO){
        rv.component = new ZSystemInfo(el, qApp);
#endif
    }

    return rv;
}

Q_EXPORT_PLUGIN2(zcm_system, ZCMSystemModule)
