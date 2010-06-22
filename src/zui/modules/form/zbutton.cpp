#include "zbutton.h"

using namespace std;

ZButton::ZButton(const ZConfig &el, QWidget *parent)
    : QPushButton(parent),
    ZWidget(el,this){
    parse(_config);
    zEvent->registerSignal(this,SIGNAL(clicked()));
}

ZButton::ZButton(const QString &text, const ZConfig &el, QWidget *parent)
    : QPushButton(text,parent),
    ZWidget(el,this){
    parse(_config);
    zEvent->registerSignal(this,SIGNAL(clicked()));
}

ZButton::ZButton(const QIcon &icon, const QString &text, const ZConfig &el, QWidget *parent)
    : QPushButton(icon,text,parent),
    ZWidget(el,this){
    parse(_config);
    zEvent->registerSignal(this,SIGNAL(clicked()));
}

void ZButton::zSetIcon(QString name){
    setIcon(ZuiUtils::getIcon(name));
}

void ZButton::parse(const ZConfig &el){
    if(!el.text().isEmpty())
	setText(el.text());
    else if(!el.attribute("value","").isEmpty())
        setText(el.attribute("value"));

    if(el.hasAttribute("icon"))
        zSetIcon(el.attribute("icon"));
}
