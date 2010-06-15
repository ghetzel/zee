#ifndef ZMAP_INFO_WIDGET_
#define ZMAP_INFO_WIDGET_

#include <iostream>
#include <QtGui>
#include <QHash>

using namespace std;

class ZMapInfoWidget : public QLabel
{
	Q_OBJECT

	public:
		ZMapInfoWidget(QString iField, QWidget *parent) : QLabel(parent){init(iField);};
	
	public slots:
		void setMapInfo(QHash<QString,QVariant> info);


	private slots:
		void showData(QVariant vdata);

	private:
		void init(QString iField);

	private:
		QString field;
		QVariant data;

	signals:
		void updated(QVariant);
};

#endif