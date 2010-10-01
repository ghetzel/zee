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

    ZEventManager *eventManager(){
	return _zevent;
    }

protected:
    ZEventManager *_zevent;
};

#endif // ZUIPLUGIN_H
