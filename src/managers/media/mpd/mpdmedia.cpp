#include "mpdmedia.h"

//using namespace std;

MpdManager::MpdManager()
{
	init();
}

void MpdManager::init()
{
	server = NULL;
	zPlayer = NULL;
	zLibrary = NULL;
	hostname = MPD_HOSTNAME;
	port = MPD_PORT;
	password = MPD_PASSWORD;

	server = mpd_new(hostname.toAscii().data(), port, password.toAscii().data());

	if(mpd_connect(server) == 0)
	{
		bConnected = true;
		emit connected();
		zPlayer = new MpdPlayer(server);
		zLibrary = new MpdLibrary(server);
		//mpd_signal_connect_status_changed(server, MpdManager::dispatcher, NULL);
	}
}

void MpdManager::dispatcher(MpdObj *mi, ChangedStatusType what, void *userdata)
{
	//if(state & MPD_CST_SONGID){}
	if(what & MPD_CST_STATE){
		switch(mpd_player_get_state(server))
		{
			case MPD_PLAYER_PLAY:
			case MPD_PLAYER_PAUSE:
			case MPD_PLAYER_STOP:
				static_cast<MpdPlayer*>(player())->dispatch(what);
				break;
			default:
				break;
		}
	}
}

bool MpdManager::isConnected()
{
	return bConnected;
}

MpdPlayer *MpdManager::player()
{
	return zPlayer;
}

MpdLibrary *MpdManager::library()
{
	return zLibrary;
}