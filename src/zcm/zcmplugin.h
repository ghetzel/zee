#ifndef ZCMPLUGIN_H
#define ZCMPLUGIN_H

#include <QtCore>
#include <zutil.h>
#include <zcm/zcmplugininterface.h>

class Zee;

/*!
  \class ZcmPlugin
  \ingroup zcm_plugins
  \brief Generic base class for ZCM plugin modules.
*/
class ZcmPlugin : public QObject, public ZcmPluginInterface{
    Q_OBJECT
    Q_INTERFACES(ZcmPluginInterface)

public:
    virtual void initialize(ZEventManager *manager){
	_zevent = manager;
	ZEventManager::initialize(_zevent);
    }

    ZEventManager *eventManager(){
	return _zevent;
    }

protected:
    ZEventManager *_zevent;
};

#endif // ZCMPLUGIN_H
