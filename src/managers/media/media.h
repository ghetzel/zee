#ifndef ZMEDIA_MANAGER_
#define ZMEDIA_MANAGER_

#include <stdlib.h>
//#include <libmpd/libmpd.h>
#include <QtCore>
#include <zevent.h>
#include "player.h"
#include "library.h"

class ZMediaManager : public QObject, public ZEvent
{
	Q_OBJECT
	public:
		virtual bool isConnected() =0;
		virtual ZMediaPlayer *player() =0;
		virtual ZMediaLibrary *library() =0;
		
	public slots:
		virtual bool invoke(QString action);

	signals:
		void connected();
};

#endif
