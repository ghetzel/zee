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

#ifndef ZINFOGRAPHMODULE_H
#define ZINFOGRAPHMODULE_H

#include <QtCore>
#include <QtGui>
#include <QtXml>
#include <zeventmanager.h>
#include <zui/zuiplugin.h>
#include <zui/zuiplugininterface.h>
#include <zui/zuiutils.h>
#include <zui/modules/infograph/zgauge.h>
#include <zui/modules/infograph/zpiegauge.h>
#include <zui/modules/infograph/zcharacterdisplay.h>

/*!
  \defgroup zui_plugins_infograph Information / Graphing
  \ingroup zui_plugins
  \brief A set of widgets for information presentation, charting, and graphing
  functions.
*/

/*!
  \class ZInfographModule
  \ingroup zui_plugins_infograph
*/
class ZInfographModule : public ZuiPlugin
{
    Q_OBJECT
    Q_INTERFACES(ZuiPluginInterface)
public:
  ZuiResult prepareWidget(const QDomElement &el, QWidget *parent);

};

#endif // ZINFOGRAPHMODULE_H
