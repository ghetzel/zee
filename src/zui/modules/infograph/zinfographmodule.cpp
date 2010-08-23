#include "zinfographmodule.h"

ZuiResult ZInfographModule::prepareWidget(const QDomElement &el,
					  QWidget *parent){

  ZuiResult zRes;
  zRes.parent = parent;
  zRes.widget = NULL;

  if(0){
#ifdef ZUI_GAUGE
  }else if(el.tagName() == ZUI_GAUGE){
    zRes.widget = new ZGauge(el,zRes.parent);
#endif // ZUI_GAUGE
#ifdef ZUI_PIEGAUGE
  }else if(el.tagName() == ZUI_PIEGAUGE){
    zRes.widget = new ZPieGauge(el,zRes.parent);
#endif // ZUI_PIEGAUGE
#ifdef ZUI_CHARACTER_DISPLAY
  }else if(el.tagName() == ZUI_CHARACTER_DISPLAY){
    zRes.widget = new ZCharacterDisplay(el,zRes.parent);
#endif // ZUI_CHARACTER_DISPLAY
  }

  return zRes;
}



Q_EXPORT_PLUGIN2(zui_infograph, ZInfographModule)
