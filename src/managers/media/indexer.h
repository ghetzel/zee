#ifndef ZMEDIA_INDEXER_
#define ZMEDIA_INDEXER_

#include <iostream>
#include <QString>
#include <QThread>
#include <zevent.h>

class ZMediaIndexer : public QThread, public ZEvent
{
	Q_OBJECT
	public slots:
		bool invoke(QString action){return true;};

	protected:
		virtual void run() =0;

	signals:
		void indexing();
		void indexFailed();
		void indexingComplete();
};

#endif
