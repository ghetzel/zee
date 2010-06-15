#ifndef ZMEDIA_LIBRARY_MPD_
#define ZMEDIA_LIBRARY_MPD_

#include <libmpd/libmpd.h>
#include <QObject>
#include <QString>
#include "zevent.h"
#include <managers/media/library.h>

class MpdLibrary : public ZMediaLibrary
{
	Q_OBJECT
	public:
		MpdLibrary(MpdObj *_server);
		QList<QHash<QString,QVariant> > query(QString search);
		QList<QHash<QString,QVariant> > getByMetafield(QString metafield);
		ZMediaIndexer *indexer();
	private:
		MpdObj *server;
};

#endif