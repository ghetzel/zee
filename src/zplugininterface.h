#ifndef ZPLUGININTERFACE_H
#define ZPLUGININTERFACE_H

#include <QtCore>
#include <QList>
#include <QtXml>
#include <QtPlugin>
#include <zconfigurable.h>
#include <zeventmanager.h>

class Zee;

/*!
  \interface ZPluginInterface
  \ingroup zeeapp
  \brief Interface for interacting with all plugins.
*/
class ZPluginInterface
{

public:
  virtual void initialize(ZEventManager *manager)=0;
};

Q_DECLARE_INTERFACE(ZPluginInterface,
		    "net.gammazeta.Zee.PluginInterface/1.0")

#endif // ZPLUGININTERFACE_H
