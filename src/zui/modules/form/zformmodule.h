#ifndef ZFORMMODULE_H
#define ZFORMMODULE_H

#include <QtGui>
#include <zutil.h>
#include <zeventmanager.h>
#include <zui/zuiplugin.h>
#include <zui/zuiplugininterface.h>
#include <zui/zuiutils.h>

#include <zbutton.h>
#include <ztogglebutton.h>
#include <ztextinput.h>
//#include <zradiobutton.h>
//#include <zcheckbox.h>
#include <zslider.h>
#include <zprogressbar.h>
#include <zlistwidget.h>

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
  ZFormModule();
  ZuiResult prepareWidget(const QDomElement &el, QWidget *parent);

};

#endif // ZFORMMODULE_H
