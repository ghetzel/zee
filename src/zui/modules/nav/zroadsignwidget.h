#ifndef ZROADSIGN_WIDGET_
#define ZROADSIGN_WIDGET_

#define ZROADSIGN_CLASS_NAME	"icon"
#define ZROADSIGN_ICON_NAME	"icon"

#include <iostream>
#include <QtCore>
#include <QtGui>
#include <zevent.h>

using namespace std;

class ZRoadsignWidget : public QWidget, public ZEvent
{
	Q_OBJECT

	public:
		ZRoadsignWidget(QWidget *parent);
		ZRoadsignWidget(QString roadstring, QWidget *parent);
		bool invoke(QString action);

	public slots:
		void setRoads(QHash<QString,QVariant> mapinfo);
		void setRoads(QString roadstring);
		void refresh();

	signals:
		void roadsChanged(QStringList*);

	private:
		void init();
	
	private:
		QStringList roads;
		QList<QIcon*> roadsigns;
};

#endif