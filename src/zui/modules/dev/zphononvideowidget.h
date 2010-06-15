#ifndef ZPHONONVIDEOWIDGET_H
#define ZPHONONVIDEOWIDGET_H

#include <QtCore>
#include <QtGui>
#include <Phonon>
#include "zevent.h"
#include "zui/zuiutils.h"
#include "zvideowidget.h"


using namespace Phonon;

class ZPhononVideoWidget : public ZVideoWidget, public ZEvent
{
  Q_OBJECT

public:
  ZPhononVideoWidget(QWidget *parent =0);
  ZPhononVideoWidget(QString uri, QWidget *parent = 0);
  void setContentSource(QString uri);

public slots:
  Q_INVOKABLE bool invoke(QString action, QString arg1,
                          QString arg2, QString arg3,
                          QString arg4, QString arg5, QString arg6);
  void play();
  void pause();
  void stop();

private:
  void init();

  VideoWidget *vWidget;
  MediaObject *_mo;
  AudioOutput *_audio;
  QList<Phonon::Path> _inputPaths;
  QList<Phonon::Path> _outputPaths;
  QString _uri;
};

#endif // ZPHONONVIDEOWIDGET_H
