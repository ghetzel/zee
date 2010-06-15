#include "zcontainerwidget.h"

ZContainerWidget::ZContainerWidget(const ZConfig &el, QWidget *parent)
    : QFrame(parent),
      ZWidget(el,this)
{
    parse(_config);
}

void ZContainerWidget::parse(const ZConfig &el){
  setLayout(ZuiUtils::getLayout(
	  el.attribute("layout", ZUI_DEFAULT_LAYOUT)));
}
