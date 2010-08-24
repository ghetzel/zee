#include "zmediamodule.h"

ZMediaModule::ZMediaModule()
    : ZuiPlugin(){
}

ZuiResult ZMediaModule::prepareWidget(const QDomElement &el, QWidget *parent){
    ZuiResult zRes;
    zRes.parent = parent;
    zRes.widget = NULL;

    if(0){
#ifdef ZUI_SEEKBAR // seekbar: media seeking and progress display
    }else if(el.tagName() == ZUI_SEEKBAR){
	zRes.widget = new ZSeekbar(el, zRes.parent);
#endif
#ifdef ZUI_VIDEO // video: advanced visualization of moving pictures
    }else if(el.tagName() == ZUI_VIDEO){
	zRes.widget = new ZVideoWidget(el, zRes.parent);
#endif
    }

    return zRes;
}

Q_EXPORT_PLUGIN2(zui_media, ZMediaModule)
