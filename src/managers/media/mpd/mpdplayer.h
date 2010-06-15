#ifndef ZMEDIA_PLAYER_MPD_
#define ZMEDIA_PLAYER_MPD_

#include <stdlib.h>
#include <libmpd/libmpd.h>
#include <QtCore>
#include <zevent.h>
#include <managers/media/player.h>

class MpdPlayer : public ZMediaPlayer
{
	public:
		friend class MpdManager;
		MpdPlayer(MpdObj *_server);
		void play();
		void pause();
		void toggle();
		void stop();
		void next();
		void previous();
		void toggleRepeat();
		void toggleShuffle();
		int currentState();

	public:
		bool invoke(QString action);

	private slots:
		void checkState(){};

	private:
		MpdObj *server;
		void dispatch(ChangedStatusType state);
};

#endif