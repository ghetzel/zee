#ifndef ZVLCVIDEOWIDGET_H
#define ZVLCVIDEOWIDGET_H

#include <QtCore>
#include <QtGui>
#include <vlc/vlc.h>
#include <zui/zuiutils.h>
#include "zvideowidget.h"

class ZVLCVideoWidget : public ZVideoWidget, public ZEvent
{
  Q_OBJECT

public:
  ZVLCVideoWidget(QWidget *parent =0);
  ZVLCVideoWidget(QString uri, QWidget *parent =0);
  ~ZVLCVideoWidget();
  void setContentSource(QString uri);
  QSize sizeHint() const;
  QSize minimumSizeHint() const;

public slots:
  bool invoke(QString action,QString arg1,QString arg2,QString arg3,
              QString arg4, QString arg5, QString arg6);
  void setVolume(int volume);
  void setPosition(qreal position);
  void stop();
  void play();
  void pause();

private:
  void init();
  void raise(libvlc_exception_t * ex);
  QString _uri;
  QSize mediaSize;
  int cVolume;
  qreal cPosition;
  MediaStates currentState;
  libvlc_exception_t vlcException;
  libvlc_instance_t * vlcInstance;
  libvlc_media_player_t * vlcPlayer;
  libvlc_media_t * vlcMedia;

private slots:
  void update();


};

#endif // ZVLCVIDEOWIDGET_H
