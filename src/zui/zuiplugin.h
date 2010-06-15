#ifndef ZUIPLUGIN_H
#define ZUIPLUGIN_H

#include <QtCore>
#include <zutil.h>
#include <zui/zuiutils.h>
#include <zui/zuiplugininterface.h>

class Zee;

/*!
  \class ZuiPlugin
  \ingroup zui_plugins
  \brief Generic base class for ZUI plugin modules.
*/
class ZuiPlugin : public QObject, public ZuiPluginInterface{
    Q_OBJECT
    Q_INTERFACES(ZuiPluginInterface)
public:
    virtual void initialize(ZEventManager *manager){
	_zevent = manager;
	ZEventManager::initialize(_zevent);
    }

    virtual QList<QString> getContainerNames(){
	return ZuiUtils::getContainerNames();
    };

    ZEventManager *eventManager(){
	return _zevent;
    }

protected:
    ZEventManager *_zevent;
};

#endif // ZUIPLUGIN_H
