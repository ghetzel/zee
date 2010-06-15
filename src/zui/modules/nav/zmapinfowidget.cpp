#include "zmapinfowidget.h"


void ZMapInfoWidget::init(QString iField)
{
	field = iField;

	connect(this, SIGNAL(updated(QVariant)), SLOT(showData(QVariant)));
}

void ZMapInfoWidget::setMapInfo(QHash<QString,QVariant> info)
{
	data = info.value(field);
	if(data.isValid())
		emit updated(data);
}


void ZMapInfoWidget::showData(QVariant vdata)
{
	setText(vdata.toString());
}
