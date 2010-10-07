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
#ifndef ZCONFIGURABLE_H
#define ZCONFIGURABLE_H

#include <QtCore>
#include <QtXml>
#include <zutil.h>

class ZConfigurable
{
public:
    typedef QDomElement ZConfig;

    ZConfigurable(const ZConfig &el, QObject *self){
	_self = self;
	_config = el;
	init();
    }
    virtual void lateInit(){};

protected:
    QObject *_self;
    ZConfig _config;
    QHash<QString,QVariant> _properties;
    virtual void parse(const ZConfig &el)=0;

    QVariant param(QString key){
	return _properties.value(key,QVariant());
    }

    QList<QDomElement> childElements(QString tagName){
	QList<QDomElement> retval;
	QDomElement nextEl;

	while(!(nextEl = _config.nextSiblingElement(tagName)).isNull()){
	    retval << nextEl;
	}

	return retval;
    }

    void scanProperties(){
        QDomNamedNodeMap attr = _config.attributes();

        for(uint i = 0; i < attr.length(); i++){
            _self->setProperty(CSTR(attr.item(i).nodeName()),
                               attr.item(i).nodeValue());
        }
    }

private:
    void init(){
    //	set ID
	if(_config.hasAttribute("id"))
	    _self->setObjectName(_config.attribute("id"));

    //	set specified value
//	if(_config.hasAttribute("value"))
//	    _self->setProperty("value", QVariant(_config.attribute("value")));

        scanProperties();

	QDomNodeList elst = _config.childNodes();
	for(uint i = 0; i < elst.length(); i++){
	    QDomElement e = elst.at(i).toElement();
	    if(e.isNull())
		continue;
	    if(e.tagName() == "zee:param")
		if(e.hasAttribute("name") && (e.hasAttribute("value") || !e.text().isEmpty()))
		    _properties.insert(e.attribute("name"),
				       QVariant(e.attribute("value",e.text())));
	}
    }
};

#endif // ZCONFIGURABLE_H
