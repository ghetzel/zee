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

#ifndef ZEVENT_HANDLER_
#define ZEVENT_HANDLER_

#include <typeinfo>
#include <iostream>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QEvent>
#include <QVariant>
#include <QHash>
#include <zutil.h>
#include <zevent.h>
#include <zui/zwidget.h>
#include <zui/zuiutils.h>

using namespace std;
using namespace ZuiUtilsNS;


/*!
  \class ZEventHandler
  \ingroup zeeapp
  \brief Manages relationships between user-generated actions in the application
  and their intended targets.

  \section recv-act Receivers and Actions
  The event system within Zee allows for the \link ZuiParser XML UI definition
  \endlink to define components and the interactions between them. A component
  advertises itself as able to be acted upon by declaring itself
  a \e receiver.  Independently of this, other components can register
  \e actions, which are designed to be passed (optionally with arguments)
  to a receiver.

  Example:

    screen@jump:home

  Here we see a typical action descriptor.  This string could find itself inside
  of an \e onclick event handler.  In such a case, whenever the object is
  clicked, it would send the action 'jump:home' to the \e screen receiver.
  The receiver can then, at its discretion, choose to ignore or interpret and
  perform the action passed to it.

  \section future-impl Future Implementation

  A more robust means of defining actions is being developed.  The syntax will
  resemble the following, and will apply to the parent widget in which it
  resides or to the widget as named in the 'for' attribute.

  \code
  <zui:actions[ for="someButton"]>
    <zui:action when="property == condition" do="screen@jump:home" />
    <zui:action on="click" do="media@cmd:play" />
    <zui:action every="3m" do="map@cmd:zoomIn" />
  </zui:actions>
  \endcode

  While these actions wouldn't be particularly useful, they demonstrate the
  versatility of the system.
  \list
  \li \b Triggers are actions that occur when a given property meets certain
  conditions and are specified using the \a when attribute.  Properties will be
  specified in more detail, but are planned to include data available from
  \e data \e managers. Such data managers will include the Zee Data Manager
  Daemon (ZDMD), D-Bus, SQL queries, or HTTP requests. More on data managers
  will be detailed in the yet-to-be-written ZDM classes.

  \li \b Handlers are actions occur when a certain event occurs within the
  application and are specified using the \a on attribute.  Events will work
  directly with the Qt signals-slots mechanism.

  \li \b Timers are actions that occur on a periodic interval, and are
  specified using the \a every attribute.
  \endlist

*/
class ZEventHandler : public QObject
{
  Q_OBJECT

public:
/*!
  Returns whether this event handler contains the receiver object \a title.
*/
  bool hasReceiver(QString title);



  QObject *receiver(QString title);
  QString handler(QString receiverTitle, QString event);
  QHash<QString,QString> handlers(QString receiverTitle);
  void registerReceiver(QObject *receiver, QString title);
  void addHandler(QString receiverTitle, QString event, QString arg);
  bool eventFilter(QObject *watched, QEvent *event);
  void invokeEventAction(QObject *watched, QString event);

public:
  static ActionDescriptor parseActionDescriptor(QString evstring);
  static ConditionString parseConditionString(QString cond);

public slots:
    void invokeAction(QString evstring);
    void invokeAction(ActionDescriptor actdesc);

private:
  QHash<QString,QObject*> _receivers;
  QHash<QString, QHash<QString,QString> > _handlers;
};

#endif
