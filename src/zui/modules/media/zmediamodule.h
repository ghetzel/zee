#ifndef ZMEDIAMODULE_H
#define ZMEDIAMODULE_H

#include <QtGui>
#include <zutil.h>
#include <zeventmanager.h>
#include <zui/zuiplugin.h>
#include <zui/zuiplugininterface.h>
#include <zui/zuiutils.h>

#include <zseekbar.h>
#include <zvideowidget.h>

/*!
  \defgroup zui_plugins_media Media Components
  \ingroup zui_plugins
  \brief Contains basic widgets for handling audio/visual media.
*/

/*!
  \class ZMediaModule
  \ingroup zui_plugins_media

  Widgets defined in this module:

  \list
  \endlist
*/
class ZMediaModule : public ZuiPlugin
{
    Q_OBJECT
    Q_INTERFACES(ZuiPluginInterface)
public:
  ZMediaModule();
  ZuiResult prepareWidget(const QDomElement &el, QWidget *parent);

};

#endif // ZMEDIAMODULE_H
