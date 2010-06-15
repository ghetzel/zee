#include "zeemedia.h"

//using namespace std;

ZeeManager::ZeeManager()
{
	init();
}

void ZeeManager::init()
{
//	server = NULL;
	zPlayer = NULL;
	zLibrary = NULL;

	bConnected = true;
	emit connected();
	zPlayer = new ZeePlayer;
	zLibrary = new ZeeLibrary;
}

bool ZeeManager::isConnected()
{
	return bConnected;
}

ZeePlayer *ZeeManager::player()
{
	return zPlayer;
}

ZeeLibrary *ZeeManager::library()
{
	return zLibrary;
}


bool ZeeManager::invoke(QString action)
{
//	fail if there is no player to control
	if(player() == NULL)
		return false;
	
	if(action == "library"){
		return library()->invoke(action);
	}

	return player()->invoke(action);
}
