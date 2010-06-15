#ifndef ZDBUSINTERFACE_H
#define ZDBUSINTERFACE_H

#include <iostream>
#include <string>
#include <QtCore>
#include <QtDBus>

using namespace std;

class ZDBusInterface : public QDBusInterface{
	Q_OBJECT

public:
	ZDBusInterface(QString s, QString p,
                       QString i=QString(),
		       QDBusConnection conn=QDBusConnection::sessionBus(),
		       QObject *parent=0);
};

#endif
