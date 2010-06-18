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
