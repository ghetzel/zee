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

#ifndef ZFORMMODULE_H
#define ZFORMMODULE_H

#include <QtGui>
#include <zutil.h>
#include <zeventmanager.h>
#include <zui/zuiplugin.h>
#include <zui/zuiplugininterface.h>
#include <zui/zuiutils.h>

#include <zframe.h>
#include <zbutton.h>
#include <ztogglebutton.h>
#include <ztextinput.h>
#include <zradiobutton.h>
//#include <zcheckbox.h>
#include <zslider.h>
#include <zprogressbar.h>
#include <zlistwidget.h>
#include <ztableview.h>

/*!
  \defgroup zui_plugins_form Forms
  \ingroup zui_plugins
  \brief Contains basic widgets for constructing input forms.
*/

/*!
  \class ZFormModule
  \ingroup zui_plugins_form

  Widgets defined in this module:

  \list
  \li \c zui:button        - a simple push button
  \li \c zui:list          - a basic item list
  \endlist
*/
class ZFormModule : public ZuiPlugin
{
    Q_OBJECT
    Q_INTERFACES(ZuiPluginInterface)
public:
  ZuiResult prepareWidget(const QDomElement &el, QWidget *parent);

};

#endif // ZFORMMODULE_H
