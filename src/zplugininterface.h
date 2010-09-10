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
