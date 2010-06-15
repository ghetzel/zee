#include "zeeplayer.h"

ZeePlayer::ZeePlayer()
{
	mo = new Phonon::MediaObject(this);
	mo->setCurrentSource(Phonon::MediaSource("/media/cortex/www/dev/Zee/dev/test.mp3"));
	aout = new Phonon::AudioOutput(Phonon::MusicCategory, this);
	ppath = Phonon::createPath(mo, aout);

	connect(mo, SIGNAL(stateChanged(Phonon::State, Phonon::State)), SIGNAL(stateChanged()));
	connect(this, SIGNAL(stateChanged()), SLOT(checkState()));
}

void ZeePlayer::checkState()
{
	Phonon::State pState = mo->state();

	switch(pState)
	{
		case Phonon::ErrorState:
			cout << "ZeeMedia: ERROR: " << mo->errorString().toStdString() << endl; flush(cout);
			break;
		case Phonon::PlayingState:
			cout << "ZeeMedia: Playing" << endl; flush(cout);
			emit playing();
			break;
		case Phonon::PausedState:
			cout << "ZeeMedia: Paused" << endl; flush(cout);
			emit paused();
			break;
		case Phonon::StoppedState:
			cout << "ZeeMedia: Stopped" << endl; flush(cout);
			emit stopped();
			break;
		case Phonon::BufferingState:
			cout << "ZeeMedia: Buffering..." << endl; flush(cout);
			emit buffering();
			break;
		default:
			cout << "ZeeMedia: State UNKNOWN" << endl; flush(cout);
			break;
	}
}


bool ZeePlayer::invoke(QString action)
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