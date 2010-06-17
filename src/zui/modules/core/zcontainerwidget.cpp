#include "zcontainerwidget.h"

ZContainerWidget::ZContainerWidget(const ZConfig &el, QWidget *parent)
    : QFrame(parent),
      ZWidget(el,this)
{
    parse(_config);
    zEvent->registerSlot(this, SLOT(hide()));
    zEvent->registerSlot(this, SLOT(show()));
    zEvent->registerSlot(this, SLOT(toggle()));
}

void ZContainerWidget::parse(const ZConfig &el){
  setLayout(ZuiUtils::getLayout(
	  el.attribute("layout", ZUI_DEFAULT_LAYOUT)));
}

void ZContainerWidget::toggle(){
    if(isHidden())
        show();
    else
        hide();
}
