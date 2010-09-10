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

#include "zdbusabstractadaptor.h"

ZDBusAbstractAdaptor::ZDBusAbstractAdaptor(QObject *parent)
    : QDBusAbstractAdaptor(parent){
    _instance = parent;
}

ZDBusAbstractAdaptor::ZDBusAbstractAdaptor(QString name, QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
    if(!name.isEmpty())
	_name = name;
    _instance = parent;
}

void ZDBusAbstractAdaptor::setInstance(QObject *instance){
    _instance = instance;
}

void ZDBusAbstractAdaptor::registerService()
{
//  if name isn't set yet...
    if(_name.isEmpty())
	if(_instance && !_instance->objectName().isEmpty())
	    _name = _instance->objectName();

    if(_instance){
	QDBusConnection::sessionBus().registerObject(ZDBUS_OPATH+_name,
						     _instance);
	QDBusConnection::sessionBus().registerService(ZDBUS_SVCNM);
	//+zApp->arg("program").toString()
    }
}
