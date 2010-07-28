#ifndef ZCLOCK_
#define ZCLOCK_

#define ZUI_CLOCK                       "zui:clock"
#define ZCLOCK_DEFAULT_WIDTH		75
#define ZCLOCK_DEFAULT_HEIGHT		30
#define ZCLOCK_DEFAULT_TIME_FORMAT	"hh:mm"
#define ZCLOCK_DEFAULT_DATE_FORMAT	"yyyy-MM-dd"

#include <QtCore>
#include <QtGui>
#include <zui/zwidget.h>
#include <zeventmanager.h>

class ZClock : public QFrame
{
  Q_OBJECT
  public:
    ZClock(QWidget *parent);
    ZClock(QString timeFormat, QWidget *parent);
    ZClock(QString timeFormat, QString dateFormat, QWidget *parent);

  public slots:
    void update();
    void setTime(QDateTime time);
    void setFormat(QString format);
    QSize sizeHint();
  private:
    void init();
    void startTimer();

  private:
    QString _timeFormat;
    QString _dateFormat;
    QDateTime _time;
    QTimer *timer;
    QLabel *cTime, *cDate;
};

#endif
