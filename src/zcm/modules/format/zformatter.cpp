/******************************************************************************
*    This file is part of Zee.
*
*    Zee is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    Zee is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with Zee.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#include "zformatter.h"

ZFormatter::ZFormatter(const ZConfig &el, QObject *parent)
    : QObject(parent),
      ZConfigurable(el,this)
{
    _formatter = NULL;
    parse(_config);

    zEvent->registerSignal(this, SIGNAL(ready(QVariant)));
    zEvent->registerSlot(this, SLOT(transform(QVariant)));
}

void ZFormatter::parse(const ZConfig &el){
    if(el.hasAttribute("type") && el.hasAttribute("method")){
	_formatter = formatter(el.attribute("type"));
	if(_formatter){
	    _formatter->setMethod(el.attribute("method"));

	    foreach(QString arg, el.attribute("value").split(" || "))
		_formatter->pushArgument(arg);

	    connect(_formatter, SIGNAL(ready(QVariant)), this, SIGNAL(ready(QVariant)));
	}
    }
}

void ZFormatter::transform(QVariant val){
    if(_formatter)
	_formatter->transform(val);
    else
	z_log_debug("ZFormatter: No formatter found.");
}


ZAbstractFormatter *ZFormatter::formatter(QString name){
    ZAbstractFormatter *rv = NULL;

//  create the proper formatter
    if(name == "string"){
	rv = new ZStringFormatter(this);
    }else if(name == "number"){
    }else if(name == "date"){
	rv = new ZDateFormatter(this);
    }

    if(rv){
	rv->setObjectName(name);
	return rv;
    }

    return NULL;
}

QString ZFormatter::type(){
    if(_formatter)
	return _formatter->objectName();
    return QString();
}
