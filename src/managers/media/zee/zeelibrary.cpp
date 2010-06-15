#include "zeelibrary.h"

ZeeLibrary::ZeeLibrary()
{
	zeedb = ZDB::getConnection();
	zIndexer = new ZeeIndexer;
//	NEED EXCEPTION HANDLER
}

ZeeIndexer *ZeeLibrary::indexer()
{
	return zIndexer;
}

QList<QHash<QString,QVariant> > ZeeLibrary::query(QString search)
{
// 	QList<QHash<QString,QVariant> q;
// 	emit queryCompleted();
// 	return q;
}

QList<QHash<QString,QVariant> > ZeeLibrary::getByMetafield(QString metafield)
{
	QSqlQuery q(zeedb);
	QList<QHash<QString,QVariant> > resultset;
	QHash<QString,QVariant> resRow;
	
	q.prepare("SELECT * FROM media.GetSetByMetafield('AUDIO',:metafield) AS (type VARCHAR(16), id INT, value TEXT, count BIGINT)");
	q.bindValue(":metafield", metafield);
	if(q.exec())
	{
		resultset.clear();

		while(q.next())
		{
			for(int i = 0; i < q.record().count(); i++)
			{
				resRow.insert(q.record().fieldName(i), q.value(i));
			}

			resultset.append(resRow);

			resRow.clear();
		}
	}

	return resultset;
}

bool ZeeLibrary::invoke(QString action)
{
//	index: tell our indexer to start
	if(action == "reindex" || action == "index"){
		indexer()->start();
	}
	return true;
}