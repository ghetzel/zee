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
