#ifndef ZMEDIA_MANAGER_MPD_
#define ZMEDIA_MANAGER_MPD_

#define MPD_HOSTNAME	"localhost"
#define MPD_PORT	6600
#define MPD_PASSWORD	""

#include <stdlib.h>
#include <libmpd/libmpd.h>
#include <QtCore>
#include <zevent.h>
#include <managers/media/media.h>
#include "mpdplayer.h"
#include "mpdlibrary.h"

class MpdManager : public ZMediaManager
{
	Q_OBJECT
	public:
		MpdManager();
		void init();
		MpdPlayer *zPlayer;
		MpdLibrary *zLibrary;
		bool isConnected();
		MpdPlayer *player();
		MpdLibrary *library();
		//MpdLibrary *indexer();
	private:
		MpdObj *server;
		QString hostname;
		int port;
		QString password;
		bool bConnected;
		void dispatcher(MpdObj *mi, ChangedStatusType what, void *userdata);
};

#endif