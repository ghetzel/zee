#ifndef ZNAVMODULE_H
#define ZNAVMODULE_H

#define ZUI_MAP       "zui:map"

#include <iostream>
#include <QtCore>
#include <QtGui>
#include <QtXml>
//#include <QtDeclarative>
#include <zui/zuiplugin.h>
#include <zui/zuiutils.h>
#include "zmapwidget/zmapwidget.h"
#include "zmapinfowidget.h"
#include "zroadsignwidget.h"

using namespace std;

/*!
  \defgroup zui_plugins_nav Navigation
  \ingroup zui_plugins
  \brief Widgets used for presenting and interacting with geospatial and
  navigation data.
*/

/*!
  \class ZNavModule
  \ingroup zui_plugins_nav
*/
class ZNavModule : public ZuiPlugin
{
    Q_OBJECT
    Q_INTERFACES(ZuiPluginInterface)
public:
  ZNavModule();
  ZuiResult prepareWidget(const QDomElement *el,
                     QWidget *currentWidget,
                     QWidget *parentWidget);

};


#endif // ZNAVMODULE_H
