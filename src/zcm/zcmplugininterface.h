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
