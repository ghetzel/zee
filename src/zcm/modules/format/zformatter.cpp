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
    : ZFormatterInterface(parent),
      ZConfigurable(el,this)
{
    _formatter = NULL;
    parse(_config);

    zEvent->registerSignal(this, SIGNAL(ready(QVariant)));
    zEvent->registerSlot(this, SLOT(transform(QVariant)));
    zEvent->registerSlot(this, SLOT(setParam(QString,QVariant)));
    zEvent->registerSlot(this, SLOT(setMethod(QString)));
}

void ZFormatter::parse(const ZConfig &el){
    if(el.hasAttribute("type") && el.hasAttribute("method")){
        _formatter = formatter(el.attribute("type"));
        if(_formatter){
            setMethod(el.attribute("method"));

            foreach(QVariant param, params()){
                z_log_debug("ZFormatter: Setting param "+params().key(param)+" = "+param.toString());
                setParam(params().key(param), param);
            }

            connect(_formatter, SIGNAL(ready(QVariant)), this, SIGNAL(ready(QVariant)));
        }
    }
}

QVariant ZFormatter::transform(QVariant val){
    if(_formatter)
        return _formatter->transform(val);

    z_log_debug("ZFormatter: No formatter found.");
    return val;
}


ZAbstractFormatter *ZFormatter::formatter(QString name){
    ZAbstractFormatter *rv = NULL;

//  create the proper formatter
    if(name == ZCM_FORMATTER_STRING){   //!         string
        rv = new ZStringFormatter(this);
    }else if(name == ZCM_FORMATTER_NUMBER){ //!     number
        rv = new ZNumberFormatter(this);
    }else if(name == ZCM_FORMATTER_DATE){ //!       date
        rv = new ZDateFormatter(this);
    }else if(name == "json"){
    }else if(name == "xslt"){
    }else if(name == "xpath"){
    }else if(name == "yaml"){
    }else if(name == ZCM_FORMATTER_REGEX){ //!      regex
        rv = new ZRegexFormatter(this);
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


void ZFormatter::setParam(QString key, QVariant value){
    if(!key.isEmpty()){
        _properties.insert(key,value);
        if(_formatter)
            _formatter->setParam(key,value);
    }
}

void ZFormatter::setMethod(QString name){
    if(_formatter){
        z_log_debug("ZFormatter: Set Method to "+name);
        _formatter->setMethod(name);
    }
}
