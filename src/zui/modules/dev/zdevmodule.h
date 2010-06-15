#ifndef ZDEVMODULE_H
#define ZDEVMODULE_H

#include <iostream>
#include <QtCore>
#include <QtGui>
#include <QtXml>
#include <QtSvg>
#include <QX11Info>
#include <zutil.h>
#include <zui/zwidget.h>
#include <zui/zuiplugin.h>
#include <zui/zuiplugininterface.h>
#include <zui/zuiutils.h>
#include <QtDeclarative>

#include "zdevlabel.h"
#include "zvideowidget.h"
#include "zphononvideowidget.h"
#include "zvlcvideowidget.h"

using namespace std;


/*!
  \defgroup zui_plugins_dev Development
  \ingroup zui_plugins
  \brief Widget development and prototyping skunkworks.
*/

/*!
  \class ZDevModule
  \ingroup zui_plugins_dev
*/
class ZDevModule : public ZuiPlugin
{
    Q_OBJECT
    Q_INTERFACES(ZuiPluginInterface)
public:
  ZDevModule();
  ZuiResult prepareWidget(const QDomElement *el,
                     QWidget *currentWidget,
                     QWidget *parentWidget);

};

#endif // ZDEVMODULE_H
