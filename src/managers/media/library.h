#ifndef ZMEDIA_LIBRARY_
#define ZMEDIA_LIBRARY_

#include <iostream>
#include <QObject>
#include <QString>
#include <QList>
#include <QHash>
#include <QVariant>
#include "zevent.h"
#include "indexer.h"

class ZMediaLibrary : public QObject, public ZEvent
{
	public:
		virtual QList<QHash<QString,QVariant> > query(QString search) =0;
		virtual QList<QHash<QString,QVariant> > getByMetafield(QString metafield) =0;

	public slots:
		virtual bool invoke(QString action){return true;};

	protected:
		virtual ZMediaIndexer *indexer() =0;

	signals:
		void queryComplete();
};

#endif
