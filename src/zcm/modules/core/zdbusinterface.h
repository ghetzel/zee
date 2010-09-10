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

#ifndef ZDBUSINTERFACE_H
#define ZDBUSINTERFACE_H

#define ZCM_DBUS_INTERFACE      "zee:dbus"
#define ZCM_DBUS_METHOD         "zee:dbus-method"
#define ZCM_DBUS_SIGNAL         "zee:dbus-signal"
#define ZCM_DBUS_DEFAULT_BUS    "session"
#define ZDBUS_INTERFACE_NAME    "remote"

#include <QtCore>
#include <QtDBus>
#include <zutil.h>
#include <zconfigurable.h>
#include <zeventmanager.h>

class ZDBusInterface : public QObject, public ZConfigurable{
	Q_OBJECT

public:
	ZDBusInterface(const ZConfig &el, QObject *parent=0);
	QDBusInterface *interface();
private:
	void parse(const ZConfig &el);
	void init(QString s, QString p, QString i=QString(),
		  QDBusConnection conn=QDBusConnection::sessionBus());

private:
    QDBusInterface *_interface;
};

#endif
