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

#include "zdbusinterface.h"

ZDBusInterface::ZDBusInterface(const ZConfig &el, QObject *parent)
    : QObject(parent),
      ZConfigurable(el,this)
{
    parse(_config);
}

void ZDBusInterface::parse(const ZConfig &el){
    if(el.hasAttribute("service") && el.hasAttribute("path")){
	QString i = el.attribute("interface","");
	QString bus = el.attribute("bus",ZCM_DBUS_DEFAULT_BUS);
	if(bus == "session")
	    init(el.attribute("service"),
		 el.attribute("path"),
		 i, QDBusConnection::sessionBus());
	else if(bus == "system")
	    init(el.attribute("service"),
		 el.attribute("path"),
		 i, QDBusConnection::systemBus());

//      if by this point the interface is created, register signals/slots
	if(_interface && el.hasChildNodes()){
	    QDomNodeList ch = el.childNodes();
	    QDomElement cel;

	    for(uint i = 0; i < ch.length(); i++){
		cel = ch.at(i).toElement();
		if(!cel.isNull() && !cel.text().isEmpty()){
		    if(cel.tagName() == ZCM_DBUS_METHOD){ //        methods
			zEvent->registerSlot(_interface,
					     ZSLOT(cel.text()));
		    }else if(cel.tagName() == ZCM_DBUS_SIGNAL){ //  signals
			zEvent->registerSignal(_interface,
					     ZSIGNAL(cel.text()));
		    }

		    z_log_debug("ZDBusInterface: IFACE="+_interface->objectName());
		}
	    }
	}
    }
}


QDBusInterface *ZDBusInterface::interface(){
    return _interface;
}

void ZDBusInterface::init(QString s, QString p, QString i, QDBusConnection conn){
    _interface = new QDBusInterface(s,p,i,conn,this);

    if(_interface->isValid()){
	_interface->setObjectName(ZDBUS_INTERFACE_NAME);
	z_log("Successfully connected: "+objectName()+"."+_interface->objectName());
	z_log("\t"+_interface->service());
	z_log("\t"+_interface->path());
	z_log("\t"+_interface->interface());
    }else{
	z_log("Connection Failed:");
	z_log("\t"+_interface->lastError().name()+": "+
		_interface->lastError().message());
    }
}
