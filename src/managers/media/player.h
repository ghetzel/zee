#ifndef ZMEDIA_PLAYER_
#define ZMEDIA_PLAYER_

#include <QtCore>
#include <zevent.h>

enum ZMediaPlayerStates
{
	ZMP_STATE_PLAYING,
	ZMP_STATE_PAUSED,
	ZMP_STATE_STOPPED,
	ZMP_STATE_SEEKING,
	ZMP_STATE_OPENING,
	ZMP_STATE_BUFFERING,
	ZMP_STATE_UNKNOWN
};

class ZMediaPlayer : public QObject, public ZEvent
{
	Q_OBJECT
	public:
		friend class ZMediaManager;
	//	player functions
		virtual void play() =0;
		virtual void pause() =0;
		virtual void toggle() =0;
		virtual void stop() =0;
		virtual void next() =0;
		virtual void previous() =0;
		virtual void toggleRepeat() =0;
		virtual void toggleShuffle() =0;
		virtual bool invoke(QString action);
	
	public slots:
		virtual void checkState() =0;

	signals:
		void stateChanged();
		void playing();
		void paused();
		void stopped();
		void buffering();
		void moveNext();
		void movePrevious();
};

#endif