#ifndef ZDEMODULE_H
#define ZDEMODULE_H

#include <QtCore>
#include <QtGui>
#include <QtXml>
#include <zutil.h>
#include <zui/zuiplugin.h>
#include <zui/zuiplugininterface.h>
#include <zui/zuiutils.h>

#include <zui/zx11/zxwindow.h>
#include <zui/zx11/zxrootwindow.h>

#include "ztaskbar.h"

#define ZUI_DESKTOP     "zui:desktop"
#define ZUI_TASKBAR     "zui:taskbar"
#define ZUI_STRUT       "zui:strut"

using namespace std;

/*!
  \defgroup zui_plugins_zde ZDE
  \ingroup zui_plugins
  \brief A set of widgets that provide core desktop environment functionality.
*/

/*!
  \class ZDEModule
  \ingroup zui_plugins_zde
*/
class ZDEModule : public ZuiPlugin
{
    Q_OBJECT
    Q_INTERFACES(ZuiPluginInterface)
public:
  ZDEModule();
  ZuiResult prepareWidget(const QDomElement &el, QWidget *parent=0);

};


#endif // ZDEMODULE_H
