/******************************************************************************
*    This file is part of Zee.
*
*    Zee is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    Zee is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with Zee.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

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
