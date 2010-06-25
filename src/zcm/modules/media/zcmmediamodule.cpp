#include "zcmmediamodule.h"

ZCMMediaModule::ZCMMediaModule(){
    ZuiUtils::initialize();
}

ZcmResult ZCMMediaModule::prepare(const QDomElement &el){
    ZcmResult rv = {NULL};

    if(0){
#ifdef ZEE_AUDIO
    }else if(el.tagName() == ZEE_AUDIO){
        ZAudioManager *c = new ZAudioManager(el,qApp);
        if(ZuiUtils::attributeTrue(el,"remote"))
            c->setAdaptor(new ZAudioAdaptor(c));
        rv.component = c;
#endif // ZEE_AUDIO
    }

    return rv;
}

Q_EXPORT_PLUGIN2(zcm_media, ZCMMediaModule)
