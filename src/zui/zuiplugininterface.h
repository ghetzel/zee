#ifndef ZUIPLUGININTERFACE_H
#define ZUIPLUGININTERFACE_H

#include <QtCore>
#include <QList>
#include <QtXml>
#include <QtPlugin>
#include <zconfigurable.h>
#include <zeventmanager.h>
#include <zplugininterface.h>

class Zee;

struct ZuiResult{
  QWidget *parent;
  QWidget *widget;
};

/*!
  \interface ZuiPluginInterface
  \ingroup zui_plugins
  \brief Interface for interacting with ZUI plugins.
*/
class ZuiPluginInterface : public ZPluginInterface
{

public:
/*!
  Instantiates new widgets and configures them based on attributes from \a el,
  placing them as children of \a parentWidget.  Containers create widgets and
  make themselves the new parent widget by setting the \c parent property to
  their own pointer in the returned \c ZuiResult structure.

  \return a populated ZuiResult containing the current widget and parent to be
  passed in the next call to this function.
*/
  virtual ZuiResult prepareWidget(const QDomElement &el,
				  QWidget *parent) =0;

/*!
  Returns a list of containers this plugin can generate.
*/
  virtual QList<QString> getContainerNames() =0;

/*!
  \fn virtual QList<QString> getElementNames() =0;

  Returns a list of elements this plugin can handle.
*/
};

Q_DECLARE_INTERFACE(ZuiPluginInterface,
		    "net.gammazeta.Zee.ZuiPluginInterface/1.0")

#endif // ZUIPLUGININTERFACE_H
