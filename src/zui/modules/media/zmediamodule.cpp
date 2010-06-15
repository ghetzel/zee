#include "zmediamodule.h"

ZMediaModule::ZMediaModule()
    : ZuiPlugin(){
}

ZuiResult ZMediaModule::prepareWidget(const QDomElement &el, QWidget *parent){
    ZuiResult zRes;
    zRes.parent = parent;
    zRes.widget = NULL;

    if(0){
#ifdef ZUI_ // _: _
    }else if(el.tagName() == ZUI_){
        //zRes.widget = new ZButton(el, zRes.parent);

#endif // ZUI_
    }

    return zRes;
}

Q_EXPORT_PLUGIN2(zui_media, ZMediaModule)
