#ifndef ZMEDIA_LIBRARY_ZEE_
#define ZMEDIA_LIBRARY_ZEE_

#include <iostream>
#include <QObject>
#include <QString>
#include <QList>
#include <QHash>
#include <QVariant>
#include <QtSql>
#include <zevent.h>
#include <zdb.h>
#include <managers/media/library.h>
#include "zeeindexer.h"

class ZeeLibrary : public ZMediaLibrary
{
	public:
		ZeeLibrary();
		QList<QHash<QString,QVariant> > query(QString search);
		QList<QHash<QString,QVariant> > getByMetafield(QString metafield);

	public slots:
		bool invoke(QString action);

	protected:
		ZeeIndexer *indexer();

	private:
		QSqlDatabase zeedb;
		ZeeIndexer *zIndexer;
};

#endif