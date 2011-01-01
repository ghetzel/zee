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

#define  ZEE_DEFAULT_LOCAL_BIND_PROPERTY        "value"

#include <QtCore>
#include <QtXml>
#include <zutil.h>
#include <zeventmanager.h>
#include <zconfigelement.h>

// HACK: Inheritable signals-slots from a generic non-QObject-descended ancestor
//  because we are extending Qt widgets/objects to create our own, we run into
//  a problem when trying to inherit signals and slots.  The ZConfigurable class
//  cannot itself inherit QObject (and therefore cannot itself contain signals
//  or slots to pass onto its children); the reason for this is because any Qt
//  class we extend has already inherited from QObject.  Thus, for this to do so
//  throws an `ambiguous base' compiler error.  The hack-solution: create
//  our own macro that includes any signals/slots we wish to be passed on to
//  descendant objects.  That way the method is technically defined within the
//  context of the implementing class, but it still looks shiny.
#define Z_OBJECT                                                               \
public slots:                                                                  \
    void setParam(QString key, QVariant value){                                \
        if(!key.isEmpty()){                                                    \
            z_log_debug("ZConfigurable: Set Param "+key+"="+value.toString()); \
            _properties.insert(key,value);                                     \
        }                                                                      \
    }                                                                          \
private:                                                                       \

typedef ZConfigElement ZConfig;

class ZConfigurable
{
public:

    ZConfigurable(const ZConfig &el, QObject *self){
        _self = self;
        _config = el;
        init();
    }

    virtual void lateInit(){
        checkBindings();
    }

    void checkBindings(){
        foreach(QString local, _bindings.keys()){
            _self->setProperty(CSTR(local),
                               zEvent->getProperty(
                                       _bindings.value(local)));
        }
    }

protected:
    QObject *_self;
    ZConfig _config;
    QVariantHash _properties;
    QHash<QString,QString> _bindings;
    virtual void parse(const ZConfig &el)=0;

    QVariant param(QString key){
        return _properties.value(key,QVariant());
    }

    QVariantHash params(){
        return _properties;
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

    //	set default parameter
        if(_config.hasAttribute("param"))
            _properties.insert(ZML_DEFAULT_PARAM_NAME, QVariant(_config.attribute("param")));

        scanProperties();

        foreach(const ZConfig param, _config.children("zee:param")){
            if(param.hasAttribute("name") && !param.value().isEmpty()){
                _properties.insert(param.attribute("name"), param.value());
            }
        }

        if(_config.hasAttribute("bind")){
            QStringList bindings = _config.attribute("bind").split(";");
            foreach(QString binding, bindings){
                QStringList localRemote = binding.split(":");
                QString local = ZEE_DEFAULT_LOCAL_BIND_PROPERTY;
                QString remote;
            //  no local property specified, use default
                if(localRemote.count() == 1){
                    remote = localRemote.at(0);

            //  local property specified, use it
                }else if(localRemote.count() == 2){
                    local = localRemote.at(0);
                    remote = localRemote.at(1);
                }

                if(!remote.isEmpty()){
                    z_log_debug("ZConfigurable: binding "+local+" -to- "+remote);
                    _bindings.insert(local, remote);
                }
            }
        }
    }
};

#endif // ZCONFIGURABLE_H
