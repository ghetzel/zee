#include "mpdplayer.h"

MpdPlayer::MpdPlayer(MpdObj *_server = NULL)
{
	server = _server;
}

void MpdPlayer::play(){ if(server){ mpd_player_play(server); }}
void MpdPlayer::pause(){ if(server){ mpd_player_pause(server); }}
void MpdPlayer::toggle(){}
void MpdPlayer::stop(){ if(server){ mpd_player_stop(server); }}
void MpdPlayer::next(){ if(server){ mpd_player_next(server); }}
void MpdPlayer::previous(){ if(server){ mpd_player_prev(server); }}
void MpdPlayer::toggleRepeat(){ if(server){ mpd_player_set_repeat(server, !mpd_player_get_repeat(server)); }}
void MpdPlayer::toggleShuffle(){ if(server){ mpd_player_set_random(server, !mpd_player_get_random(server)); }}


void MpdPlayer::dispatch(ChangedStatusType state)
{
	if(state & MPD_PLAYER_PLAY){
		emit playing();
	}else if(state & MPD_PLAYER_PAUSE){
		emit paused();
	}else if(state & MPD_PLAYER_STOP){
		emit stopped();
	}
}

bool MpdPlayer::invoke(QString action)
{
	if(!server)
		return false;

	if(action == "play")		// player: play
		play();
	else if(action == "pause")	// player: pause
		pause();
	else if(action == "stop")	// player: stop
		stop();
	else if(action == "next")	// player: next
		next();
	else if(action == "previous")	// player: previous
		previous();

	return true;
}

int MpdPlayer::currentState()
{
	switch(mpd_player_get_state(server))
	{
		case MPD_PLAYER_PLAY:
			return ZMP_STATE_PLAYING;
		case MPD_PLAYER_PAUSE:
			return ZMP_STATE_PAUSED;
		case MPD_PLAYER_STOP:
			return ZMP_STATE_STOPPED;
		default:
			return ZMP_STATE_UNKNOWN;
	}
}