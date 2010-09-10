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

#ifndef ZCLOCK_H
#define ZCLOCK_H

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

#endif // ZCLOCK_H
