#ifndef ZMEDIA_PLAYER_ZEE_
#define ZMEDIA_PLAYER_ZEE_

#include <iostream>
#include <Phonon>
#include <managers/media/player.h>

using namespace std;

class ZeePlayer : public ZMediaPlayer
{
	public:
		ZeePlayer();
		void play(){mo->play();};
		void pause(){mo->pause();};
		void toggle(){};
		void stop(){mo->stop();};
		void next(){};
		void previous(){};
		void toggleRepeat(){};
		void toggleShuffle(){};
		bool invoke(QString action);
	
	private:
		Phonon::State state();

	private:
		Phonon::MediaObject *mo;
		Phonon::AudioOutput *aout;
		Phonon::Path ppath;

	private slots:
		void checkState();

	signals:
		void backendStateChanged();
};

#endif