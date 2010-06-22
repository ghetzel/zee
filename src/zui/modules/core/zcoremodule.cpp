#include "zcoremodule.h"

ZCoreModule::ZCoreModule()
    : ZuiPlugin(){
    ZuiUtils::registerContainerElement(ZUI_CONTAINER);
    ZuiUtils::registerContainerElement(ZUI_SCREEN);
    ZuiUtils::registerContainerElement(ZUI_SCREENMGR);
    ZuiUtils::registerContainerElement("zui:dock");
}

ZuiResult ZCoreModule::prepareWidget(const QDomElement &el, QWidget *parent){
    ZuiResult zRes;
    zRes.parent = parent;
    zRes.widget = NULL;

    if(0){
#ifdef ZUI_APPLICATION // application: the app window itself
    }else if(el.tagName() == ZUI_APPLICATION){
	zRes.widget = new ZWindow(el);
	zRes.parent = zRes.widget;
#endif // ZUI_APPLICATION
#ifdef ZUI_SCREENMGR // screens: manages task visibility/navigation
    }else if(el.tagName() == ZUI_SCREENMGR){
	zRes.widget = new ZScreenManager(el, zRes.parent);
	zRes.parent = zRes.widget;
#endif // ZUI_SCREENMGR
#ifdef ZUI_CONTAINERS // containers: they hold things
    }else if(ZuiUtils::getContainerNames().contains(el.tagName())){
	//  add currentWidget to a new containing frame
	zRes.widget = new ZContainerWidget(el, zRes.parent);

//	if adding a screen to the screen manager, call its add method direct,
	if(el.tagName() == ZUI_SCREEN){	    
            ZScreenManager *scrman = QCAST(ZScreenManager*,zRes.parent);
            if(scrman)
                scrman->addScreen(zRes.widget, el.attribute("name", NULL));
	}

	zRes.parent = zRes.widget;
#endif // ZUI_CONTAINERS
//#ifdef ZUI_SCREEN // screen: put it in a manager
//    }else if(el.tagName() == ZUI_SCREEN){
//	//  only create the screen if our direct parent is a ZScreenManager
//	ZScreenManager *scrman = QCAST(ZScreenManager*,zRes.parent);
//	if(scrman){
//	    zRes.widget = new ZScreen(el, scrman);
//
//	    //  change the operating parent widget to this new one we just built
//	    zRes.parent = zRes.widget;
//	}
//
//#endif // ZUI_SCREEN
#ifdef ZUI_TEXT // text: generic text label
    }else if(el.tagName() == "zui:text"){
	zRes.widget = new ZLabel(el, zRes.parent);

#endif // ZUI_TEXT
#ifdef ZUI_IMAGE // image: generic image display
    }else if(el.tagName() == ZUI_IMAGE){
	zRes.widget = new QLabel("", zRes.parent, 0);

#endif // ZUI_IMAGE
    }

    return zRes;
}

Q_EXPORT_PLUGIN2(zui_core, ZCoreModule)
