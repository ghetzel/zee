#include "player.h"

bool ZMediaPlayer::invoke(QString action)
{
	if(action == "play")
		play();
	else if(action == "pause")
		pause();
	else if(action == "toggle")
		toggle();
	else if(action == "stop")
		stop();
	else if(action == "next")
		next();
	else if(action == "previous")
		previous();
	else if(action == "toggleRepeat")
		toggleRepeat();
	else if(action == "toggleShuffle")
		toggleShuffle();

	return true;
}