#ifndef ZCONFIGURABLE_H
#define ZCONFIGURABLE_H

#include <QtCore>
#include <QtXml>

class ZConfigurable
{
public:
    typedef QDomElement ZConfig;

    ZConfigurable(const ZConfig &el, QObject *self){
	_self = self;
	_config = el;
	init();
    }



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

private:
    void init(){
    //	set ID
	if(_config.hasAttribute("id"))
	    _self->setObjectName(_config.attribute("id"));

    //	set specified value
	if(_config.hasAttribute("value"))
	    _self->setProperty("value", QVariant(_config.attribute("value")));

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
