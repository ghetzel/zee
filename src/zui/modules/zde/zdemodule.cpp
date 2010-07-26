#include "zdemodule.h"

ZDEModule::ZDEModule(){
  ZXServer::initialize();
  //ZuiUtils::registerContainerElement(ZUI_TASKBAR);
}


ZuiResult ZDEModule::prepareWidget(const QDomElement &el, QWidget *parent){
  ZuiResult zRes;
  zRes.parent = parent;
  zRes.widget = NULL;

  if(el.tagName() == ZUI_DESKTOP){
    zRes.widget = NULL;
    //ZuiUtils::prepareContainer(zRes.widget, el);

    zRes.parent = zRes.widget;


#ifdef ZUI_TASKBAR
  }else if(el.tagName() == ZUI_TASKBAR){
    zRes.widget = new ZTaskbar(el, zRes.parent);
    //zRes.widget->setProperty("hide-text1",QVariant("y"));
    zRes.widget->setLayout(ZuiUtils::getLayout(el.attribute("layout")));
#endif  //  ZUI_TASKBAR
#ifdef ZUI_STRUT
  }else if(el.tagName() == ZUI_STRUT){
    if(el.hasAttribute("position")){
      ZXWindow *zxApp = new ZXWindow(qApp->topLevelWidgets().first()->winId());
      QString pos = el.attribute("position");

      if( (pos=="n" || pos=="s") && el.hasAttribute("height") )
        zxApp->addStrut(QSize(0,el.attribute("height").toInt()),
                        (pos=="n" ? NorthEdge : SouthEdge));
      else if( (pos=="e" || pos=="w") && el.hasAttribute("width") )
        zxApp->addStrut(QSize(el.attribute("width").toInt(),0),
                        (pos=="e" ? EastEdge : WestEdge));
    }
#endif  //  ZUI_STRUT
  }

  return zRes;
}

Q_EXPORT_PLUGIN2(zmod_zde, ZDEModule)
