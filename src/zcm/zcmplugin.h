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
