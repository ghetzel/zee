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
#ifdef ZCM_METAREADER
    }else if(el.tagName() == ZCM_METAREADER){
        rv.component = new ZMetaReader(el,qApp);

#endif // ZCM_METAREADER
    }

    return rv;
}

Q_EXPORT_PLUGIN2(zcm_media, ZCMMediaModule)
