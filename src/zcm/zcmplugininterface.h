#ifndef ZCMPLUGININTERFACE_H
#define ZCMPLUGININTERFACE_H

#define ZEE_COMPONENTS		"zee:components"

#include <QtCore>
#include <QList>
#include <QtXml>
#include <QtPlugin>
#include <zconfigurable.h>
#include <zeventmanager.h>
#include <zplugininterface.h>

class Zee;

struct ZcmResult{
  QObject *component;
};

/*!
  \interface ZcmPluginInterface
  \ingroup zcm_plugins
  \brief Interface for interacting with ZCM plugins.
*/
class ZcmPluginInterface : public ZPluginInterface
{
public:
  virtual ZcmResult prepare(const QDomElement &el) =0;
};

Q_DECLARE_INTERFACE(ZcmPluginInterface,
		    "net.gammazeta.Zee.ZcmPluginInterface/1.0")

#endif // ZCMPLUGININTERFACE_H
