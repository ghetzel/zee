#include "zclock.h"

ZClock::ZClock(QWidget *parent)
  : QFrame(parent)
{
  init();
}

ZClock::ZClock(QString timeFormat, QWidget *parent)
  : QFrame(parent){
  _timeFormat = timeFormat;
  init();
}

ZClock::ZClock(QString timeFormat, QString dateFormat, QWidget *parent)
  : QFrame(parent){
  _timeFormat = timeFormat;
  _dateFormat = dateFormat;
  init();
}

void ZClock::init()
{
  cTime = NULL;
  cDate = NULL;

  setLayout(new QVBoxLayout);  

  layout()->setSpacing(0);
  layout()->setContentsMargins(0,0,0,0);

  if(!_timeFormat.isEmpty()){
    cTime = new QLabel(this);
    cTime->setAlignment(Qt::AlignCenter);
    cTime->setObjectName("time");
    layout()->addWidget(cTime);
  }

  if(!_dateFormat.isEmpty()){
    cDate = new QLabel(this);
    cDate->setAlignment(Qt::AlignCenter);
    cDate->setObjectName("date");
    layout()->addWidget(cDate);
  }

  update();
  startTimer();
}

QSize ZClock::sizeHint()
{
  return QSize(ZCLOCK_DEFAULT_WIDTH, ZCLOCK_DEFAULT_HEIGHT);
}

void ZClock::startTimer()
{
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(1000);
}

void ZClock::setTime(QDateTime time)
{
  _time = time;
}

void ZClock::setFormat(QString format)
{
  _timeFormat = format;
}

void ZClock::update()
{
  setTime(QDateTime::currentDateTime());
  if(cTime)
    cTime->setText(_time.toString(_timeFormat));
  if(cDate)
    cDate->setText(_time.toString(_dateFormat));
}
