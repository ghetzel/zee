#ifndef ZWIDGET_H
#define ZWIDGET_H

#include <QtCore>
#include <QtGui>
#include <zconfigurable.h>
#include <zeventmanager.h>
#include <zui/zuiutils.h>

class ZWidget : public ZConfigurable{

public:
    ZWidget(const ZConfig &el, QWidget *self)
	: ZConfigurable(el,self){
	parse(_config);
    }

private:
    void parse(const ZConfig &el){
    //	tell the object what element spawned it (for style ~*MAGIC*~)
	_self->setProperty("element", QVariant(el.tagName()));

    //	set style classes
	if(el.hasAttribute("class"))
	    _self->setProperty("cls", QVariant(el.attribute("class").split(" ")));
    }
};

#endif // ZWIDGET_H
