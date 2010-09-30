#include "zcmsystemmodule.h"

ZCMSystemModule::ZCMSystemModule(){}

ZcmResult ZCMSystemModule::prepare(const QDomElement &el){
    ZcmResult rv;

    if(0){
#ifdef ZCM_
    }else if(el.tagName() == ZCM_){
        //rv.component = new ZDingus(el,qApp);
        //rv.parent = rv.component;
#endif
    }

    return rv;
}

Q_EXPORT_PLUGIN2(zcm_system, ZCMSystemModule)
