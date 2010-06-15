#ifndef ZVIDEOWIDGET_H
#define ZVIDEOWIDGET_H

#include <QtCore>
#include <QtGui>
#include <zui/zuiutils.h>
#include "zevent.h"

using namespace ZuiUtilsNS;

class ZVideoWidget : public QWidget
{
  Q_OBJECT

public:
  ZVideoWidget(QWidget *parent =0) : QWidget(parent){};
  virtual void setContentSource(QString uri) =0;

public slots:
  virtual void stop() =0;
  virtual void play() =0;
  virtual void pause() =0;

signals:
  void volumeChanged(int volume);
  void positionChanged(qreal position);
  void playstateChanged(MediaStates state);
  void contentSourceChanged(QString uri);
};

#endif // ZVIDEOWIDGET_H
