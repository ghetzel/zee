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
#include <zwebbrowser.h>


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
