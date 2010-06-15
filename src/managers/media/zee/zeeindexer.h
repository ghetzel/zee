#ifndef ZMEDIA_INDEXER_ZEE_
#define ZMEDIA_INDEXER_ZEE_

#include <unistd.h>
#include <iostream>
#include <QtCore>
#include <QtSql>
#include <QHash>
#include <QMultiHash>
#include <zevent.h>
#include <zdb.h>
#include <managers/media/indexer.h>
#include <managers/media/object.h>



class ZeeIndexer : public ZMediaIndexer
{
	Q_OBJECT

	protected:
		void run();

	private:
		QList<QString> monitoredPaths;
		QSqlDatabase zeedb;
		QMultiHash<QString,QString> metafields;
		QHash<QString,int> mfieldmap;
	private:
/*!
	\name Reindex
	\brief Initiates a (re)indexing of the library based on monitored paths
	\return whether the index was successful or not
*/
		bool reindex();
		bool initDb();
		void cleanup();
		void loadDataValues();
		void loadMonitoredPaths();
		bool indexPath(QString uri);
		bool importItem(QString uri, ZMediaObject *metaParser);
};

#endif
