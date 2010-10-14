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

#ifndef ZEVENTMANAGER_H
#define ZEVENTMANAGER_H

#include <cstdio>
#include <QObject>
#include <QString>
#include <QHash>
#include <QList>
#include <QMultiHash>
#include <QPair>
#include <QMetaMethod>
#include <zutil.h>
#include <zeventobject.h>
#include <zeventrelationship.h>

#define zEventKey(e)                QString(e).toLower()
#define ZEV_SEPARATOR               "."
#define ZEV_POSITIONAL_SEPARATOR    ","
#define zEvent                      ZEventManager::instance()


/*!
  \class ZEventManager
  \ingroup zeeapp
  \brief The event manager is responsible for coordinating communication between
  named components dynamically created at runtime.

  Components, like other Qt objects, emit signals and provide slots to allow
  for generic communication between them.  However, this system falls short in
  that it requires the client to have knowledge of the specific data types
  involved in the connection, and is limited by the fact that signals may not
  necessarily provide the information a slot needs to perform a task, but this
  does not occlude the need to perform said task.

  Example:

  A user wishes to create a simple web browser application.  The browser will
  utilize the zui:browser component for viewing web pages, a text input box for
  viewing and changing the URL, and a button to Go to the URL specified in the
  text box. The signals and slots for these components might look like this:

  Browser{	// objectName = "web"
    public slots:
	void load(QString url);
    ...
  }

  TextInput{	// objectName = "address"
    Q_PROPERTY(QString text READ text)
    ...
  }

  Button{	// objectName = "go"
    signals:
	void clicked();
    ...
  }

  Herein lies the problem.  The button emits a clicked() signal without any
  argument.  This is the desired behavior, as the button should not need to be
  specialized in any way in order to serve the purpose of informing the
  application that it has been clicked. But where will the data for the \a url
  argument to Browser's load() slot come from?  The answer is a surrogate
  property.

  Surrogate properties act as "stand-ins" for missing data.  The button itself
  does not contain the necessary data to inform the browser on where to go next,
  however the TextInput does have this information in the form of its \a text
  property.

  Using the ZEventManager \a map() method, this relationship between the three
  components can easily be expressed.  In the case where type-compatible signals
  and slots are being connected, a simple call like the following will suffice:

    map("button.clicked", "application.quit")

  Because both the signal and the slot take zero arguments, this works straight
  out. However, \a map() can also take a third, optional parameter \a via. When
  \a via is set to point to an object in the form of "objectName.propertyName",
  the value of this property will be passed along to the receiver when the
  sender emits its signal. Given our example browser, the call to \a map() would
  be:

    map("go.clicked", "web.load", "address.text")

  Now, when the Go button's clicked() event fires, the browser's load() slot
  will be called, taking the value of address' text property at the time the
  signal was emitted.  Because Qt properties are of type QVariant, they can take
  on many forms.  The most appropriate type for the property is automatically
  chosen based on the data type(s) the slot is expecting.
*/
class ZEventManager : public QObject
{
    Q_OBJECT
public:
    void registerSignal(QObject *source, const char *signal);
    void registerSlot(QObject *receiver, const char *slot);
    void map(QString from, QString to, QString via=QString(),
             QString formatters=QString(), bool direct=true);
    QObject *findObject(QString methodString, bool objectOnly=false);
    QVariant getProperty(QString methodString);
    static void initialize(ZEventManager *instance=0);
    static ZEventManager *instance();

private:
    void init();
    void registerMethod(QMetaMethod::MethodType type,
			QObject *object, const char *method);
    void insertMethod(QObject *object, const char *method,
		      QHash<QObject*,ZEventObject> &store);

    QHash<QObject*,ZEventObject> _signals;
    QHash<QObject*,ZEventObject> _slots;
    QList<ZEventRelationship*> _mappings;
    static ZEventManager *_instance;
};

#endif // ZEVENTMANAGER_H
