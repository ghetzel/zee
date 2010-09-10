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

#ifndef ZEXTRASMODULE_H
#define ZEXTRASMODULE_H

#include <QtCore>
#include <QtGui>
#include <QtXml>
#include <QtWebKit>
#include <zutil.h>
#include <zui/zuiplugin.h>
#include <zui/zuiplugininterface.h> // forward decl?
#include <zui/zuiutils.h>
#include "zclock.h"
#include "zfilebrowser.h"
#include "zfolderview.h"
#include <zhtmlfolderview.h>
#include <zwebbrowser.h>
#include <zterminal.h>


/*!
  \defgroup zui_plugins_extras Extras
  \ingroup zui_plugins
  \brief A set of more specialized widgets that enrich the user experience.
*/

/*!
  \class ZExtrasModule
  \ingroup zui_plugins_extras
*/
class ZExtrasModule : public ZuiPlugin
{
    Q_OBJECT
    Q_INTERFACES(ZuiPluginInterface)
public:
  ZExtrasModule();
  ZuiResult prepareWidget(const QDomElement &el, QWidget *parent);

};

#endif // ZEXTRASMODULE_H
