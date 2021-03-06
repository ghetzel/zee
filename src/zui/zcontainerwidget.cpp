#include "zcontainerwidget.h"

ZContainerWidget::ZContainerWidget(const ZConfig &el, QWidget *self)
    : ZWidget(el,self)
{
    parse(_config);
}

void ZContainerWidget::parse(const ZConfig &el){
    widget()->setLayout(ZuiUtils::getLayout(
            el.attribute("layout", ZUI_DEFAULT_LAYOUT)));

    if(el.hasAttribute("align")){
        _self->setProperty("align",el.attribute("align"));
        widget()->layout()->setAlignment(
                ZuiUtils::getAlignment(el.attribute("align")));
    }

    if(el.hasAttribute("spacing"))
        widget()->layout()->setSpacing(qRound(el.attribute("spacing").toFloat()));

}
