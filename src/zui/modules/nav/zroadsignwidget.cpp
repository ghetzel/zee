#include "zroadsignwidget.h"

ZRoadsignWidget::ZRoadsignWidget(QWidget *parent) : QWidget(parent){init();}

ZRoadsignWidget::ZRoadsignWidget(QString roadstring, QWidget *parent) : QWidget(parent)
{
	init();
	setRoads(roadstring);
}

void ZRoadsignWidget::init()
{
	setLayout(new QHBoxLayout);

//	on road change, update display
	connect(this, SIGNAL(roadsChanged(QStringList*)), SLOT(refresh()));
}

void ZRoadsignWidget::setRoads(QHash<QString,QVariant> mapinfo)
{
	QVariant rd = mapinfo.value("road");
	if(rd.isValid())
		setRoads(rd.toString());
}

void ZRoadsignWidget::setRoads(QString roadstring)
{
	QRegExp roadScan("\\s+/\\s+");
	QRegExp roadDesg("([A-Za-z]{1,4})[ -_]*([\\d\\+&]+).*");
	QStringList _roadParts;
	QStringList _roads = roadstring.split(roadScan, QString::SkipEmptyParts);
	QList<QWidget*> curRoads;
	QString iconFileName;
		
//	clear existing roads
	roadsigns.clear();
	curRoads = findChildren<QWidget*>(ZROADSIGN_ICON_NAME);
	foreach(QWidget *cRoad, curRoads)
		delete cRoad;

//	for each road...
//		if road (rd) matches a parseable format...
//			if the parse went well...
//				if a graphic for this road exists...
//					Make it so.
	foreach(QString rd, _roads){
		rd = rd.replace("(", "CR-").replace(")","");
		if(roadDesg.indexIn(rd) >= 0)
			if(roadDesg.numCaptures() >= 2)
				if(QFile::exists((iconFileName = "gfx/signs/"+roadDesg.cap(1).toLower()+"/"+roadDesg.cap(2).toLower()+".svg")))
					roadsigns.append(new QIcon(iconFileName));
	}

	emit roadsChanged(&roads);
}


void ZRoadsignWidget::refresh()
{
	QLabel *iconC;
	foreach(QIcon *icon, roadsigns)
	{
		iconC = new QLabel(this);
		iconC->setPixmap(icon->pixmap(64,56));
		iconC->setProperty("cls", ZROADSIGN_CLASS_NAME);
		iconC->setObjectName(ZROADSIGN_ICON_NAME);
		layout()->addWidget(iconC);
	}
}

bool ZRoadsignWidget::invoke(QString action)
{
	if(action == "update")
		refresh();

	return true;
}