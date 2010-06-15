#ifndef ZMEDIA_MANAGER_ZEE_
#define ZMEDIA_MANAGER_ZEE_

#include <QtCore>
#include <zevent.h>
#include <managers/media/media.h>
#include "zeeplayer.h"
#include "zeelibrary.h"


class ZeeManager : public ZMediaManager
{
	public:
		ZeeManager();
		bool isConnected();
		ZeePlayer *player();
		ZeeLibrary *library();
		bool invoke(QString action);
	private:
		void init();
		bool bConnected;
		ZeePlayer *zPlayer;
		ZeeLibrary *zLibrary;
};

#endif