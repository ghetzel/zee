#include <iostream>
#include <string>
#include <QtCore>
#include <QtGui>
#include <QApplication>
#include <zdbusinterface.h>

using namespace std;

int main(int argc, char *argv[]){

	QApplication app(argc,argv);

	QFrame root;
	QLineEdit edit("DO IT");
	QPushButton b;

//	ZDBusInterface notify("org.freedesktop.Notifications",
//			      "/org/freedesktop/Notifications",
// 			      "org.freedesktop.Notifications");
	//QDBusMessage rv;
	//rv = notify.call("Notify", "zee-dbustest", uint(0), "info", "Summary", "Body", QStringList(), QVariantMap(), 1000);


	QDBusInterface pidgin("im.pidgin.purple.PurpleService",
			      "/im/pidgin/purple/PurpleObject",
 			      "im.pidgin.purple.PurpleInterface");
	
	QObject::connect(&pidgin, SIGNAL(ConversationCreated(int)),
			 qApp, SLOT(quit()));	
	QObject::connect(&b, SIGNAL(clicked()),
			 &pidgin, SLOT(PurpleBlistShow()));	

	root.setLayout(new QHBoxLayout);
	root.layout()->addWidget(&edit);
	root.layout()->addWidget(&b);
	root.show();		
	return app.exec();
}
