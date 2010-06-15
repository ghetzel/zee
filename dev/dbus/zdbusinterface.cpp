#include "zdbusinterface.h"

ZDBusInterface::ZDBusInterface(QString s, QString p, QString i,
	QDBusConnection conn, QObject *parent)
  : QDBusInterface(s, p, i, conn, parent){ 
	
	if(isValid()){
		cout << "Successfully connected: " << endl;
		cout << "\t" << service().toStdString() << endl;
		cout << "\t" << path().toStdString() << endl;
		cout << "\t" << interface().toStdString() << endl;
	}else{
		cout << "Connection Failed:" << endl;
		cout << "\t" << lastError().name().toStdString() << ": " << 
			lastError().message().toStdString() << endl;	
	}

	flush(cout);
}
