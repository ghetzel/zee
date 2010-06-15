#include "znavmodule.h"

ZNavModule::ZNavModule(){
  ZuiUtils::registerContainerElement(ZUI_MAP);
}

ZuiResult ZNavModule::prepareWidget(const QDomElement *el,
                                       QWidget *currentWidget,
                                       QWidget *parentWidget){
  ZuiResult zRes;
  zRes.parent = parentWidget;
  zRes.widget = currentWidget;
  QWidget *newWidget = NULL;

  if(el->tagName() == ZUI_MAP){
    newWidget = new ZMapWidget(zRes.parent);

    //ZuiUtils::prepareLayout(newWidget, el);


//  set latitude/longitude
    if(el->hasAttribute("lon") && el->hasAttribute("lat")){
      QPointF cCoords(el->attribute("lon").toDouble(), el->attribute("lat").toDouble());
      static_cast<ZMapWidget*>(newWidget)->setCenter(cCoords);
    }

//  set zoom
    if(el->hasAttribute("zoom"))
      static_cast<ZMapWidget*>(newWidget)->zoomTo(el->attribute("zoom").toInt());

    zRes.parent = newWidget;
  }

  zRes.widget = newWidget;
  return zRes;
}

Q_EXPORT_PLUGIN2(zmod_nav, ZNavModule)
