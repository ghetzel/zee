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

#ifndef ZUIPLUGININTERFACE_H
#define ZUIPLUGININTERFACE_H

#include <QtCore>
#include <QList>
#include <QtXml>
#include <QtPlugin>
#include <zconfigurable.h>
#include <zui/zstyle.h>
#include <zeventmanager.h>

class Zee;

struct ZuiResult{
    QWidget *widget;
    QWidget *parent;
    ZuiResult() : widget(NULL), parent(NULL){}
};

/*!
  \interface ZuiPluginInterface
  \ingroup zui_plugins
  \brief Interface for interacting with ZUI plugins.
*/
class ZuiPluginInterface
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
  virtual void initialize(ZEventManager *manager, ZStyle *style)=0;
};

Q_DECLARE_INTERFACE(ZuiPluginInterface,
                    "net.gammazeta.Zee.ZuiPluginInterface/1.0")

#endif // ZUIPLUGININTERFACE_H
