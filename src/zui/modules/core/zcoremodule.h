#ifndef ZCOREMODULE_H
#define ZCOREMODULE_H

#define ZUI_CONTAINERS
#define ZUI_IMAGE           "zui:image"

#include <iostream>
#include <QtCore>
#include <QtGui>
#include <QtXml>
#include <zutil.h>
#include <zeventmanager.h>
#include <zui/zuiplugin.h>
#include <zui/zuiplugininterface.h>
#include <zui/zuiutils.h>
#include <zui/layouts/zflowlayout.h>

#include <zwindow.h>
#include <zcontainerwidget.h>
#include <zlabel.h>
#include <zscreenmanager.h>
#include <zscreen.h>
#include <zspacer.h>

#ifdef Q_WS_X11
#include <zui/zx11/zxrootwindow.h>
#endif

using namespace std;


/*!
  \defgroup zui_plugins_core Core
  \ingroup zui_plugins
  \brief Contains basic widgets that provide core UI functionality.
*/

/*!
  \class ZCoreModule
  \ingroup zui_plugins_core

  Widgets defined in this module:

  \list
  \li \c zui:application   - the main application window
  \li \c zui:container     - a generic element that can hold child elements and
			     has a layout
  \li \c zui:screens       - a manager that allows multiple screens to be
			     viewed, one at a time
  \li \c zui:screen        - a single instance of a screen
  \li \c zui:header        - a top-aligned container
  \li \c zui:footer        - a bottom-aligned container
  \li \c zui:text          - a text label
  \li \c zui:button        - a simple push button
  \li \c zui:list          - a basic item list
  \endlist
*/
class ZCoreModule : public ZuiPlugin
{
    Q_OBJECT
    Q_INTERFACES(ZuiPluginInterface)
public:
  ZCoreModule();
  ZuiResult prepareWidget(const QDomElement &el, QWidget *parent=0);

};

#endif // ZCOREMODULE_H
