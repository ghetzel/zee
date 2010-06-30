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
  if(el.hasAttribute("align"))
      setProperty("align",el.attribute("align"));
}

void ZContainerWidget::toggle(){
    if(isHidden())
        show();
    else
        hide();
}

Qt::Alignment ZContainerWidget::alignment(){
    if(layout())
        return layout()->alignment();
    return (Qt::AlignTop | Qt::AlignLeft);
}

void ZContainerWidget::setAlignment(Qt::Alignment alignment){
    if(layout())
        layout()->setAlignment(alignment);
}
