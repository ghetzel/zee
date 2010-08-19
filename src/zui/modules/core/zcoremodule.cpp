#include "zcoremodule.h"

ZCoreModule::ZCoreModule()
    : ZuiPlugin(){
    ZuiUtils::registerContainerElement(ZUI_CONTAINER);
    ZuiUtils::registerContainerElement(ZUI_SCREEN);
    ZuiUtils::registerContainerElement(ZUI_SCREENMGR);
    ZuiUtils::registerContainerElement(ZUI_SPLITTER);
    ZuiUtils::registerContainerElement(ZUI_PANE);
    ZuiUtils::registerContainerElement("zui:dock");
}

ZuiResult ZCoreModule::prepareWidget(const QDomElement &el, QWidget *parent){
    ZuiResult zRes;
    zRes.parent = parent;
    zRes.widget = NULL;

    if(0){
#ifdef ZUI_APPLICATION // application: the app window itself
    }else if(el.tagName() == ZUI_APPLICATION){        
        ZWindow *w = new ZWindow(el);
        zRes.widget = w->rootSurface();
        zRes.parent = zRes.widget;

#endif // ZUI_APPLICATION
#ifdef ZUI_SCREENMGR // screens: manages task visibility/navigation
    }else if(el.tagName() == ZUI_SCREENMGR){
        zRes.widget = new ZScreenManager(el, zRes.parent);
        zRes.parent = zRes.widget;
#endif // ZUI_SCREENMGR
#ifdef ZUI_SCREENMGR // splitter: resizable child panes
    }else if(el.tagName() == ZUI_SPLITTER){
        zRes.widget = new ZSplitter(el, zRes.parent);
        zRes.parent = zRes.widget;
#endif // ZUI_SCREENMGR
#ifdef ZUI_SPACER
    }else if(el.tagName() == ZUI_SPACER){
        zRes.widget = new ZSpacer(el, zRes.parent);
#endif // ZUI_SPACER
#ifdef ZUI_CONTAINERS // containers: they hold things
    }else if(ZuiUtils::getContainerNames().contains(el.tagName())){
	//  add currentWidget to a new containing frame
	zRes.widget = new ZContainerWidget(el, zRes.parent);

//	if adding a screen to the screen manager, call its add method direct,
	if(el.tagName() == ZUI_SCREEN){	    
            ZScreenManager *obj = QCAST(ZScreenManager*,zRes.parent);
            if(obj)
                obj->addScreen(zRes.widget, el.attribute("name", NULL));
        }else if(el.tagName() == ZUI_PANE){
            ZSplitter *obj = QCAST(ZSplitter*,zRes.parent);
            if(obj){
                obj->addWidget(zRes.widget);                
            }
        }

	zRes.parent = zRes.widget;
#endif // ZUI_CONTAINERS
#ifdef ZUI_TEXT // text: generic text label
    }else if(el.tagName() == "zui:text"){
	zRes.widget = new ZLabel(el, zRes.parent);

#endif // ZUI_TEXT
#ifdef ZUI_IMAGE // image: generic image display
    }else if(el.tagName() == ZUI_IMAGE){
        zRes.widget = new ZLabel(el, zRes.parent);

#endif // ZUI_IMAGE
    }

    return zRes;
}

Q_EXPORT_PLUGIN2(zui_core, ZCoreModule)
