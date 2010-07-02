#ifndef ZUI_PARSER_
#define ZUI_PARSER_

#include <iostream>
#include <QObject>
#include <QApplication>
#include <QtGui>
#include <QtXml>
#include <QPluginLoader>
#include <QList>

#include <zconfigurable.h>
#include <zeventhandler.h>
#include <zplugininterface.h>
#include <zcm/zcmplugin.h>
#include <zcm/zcmplugininterface.h>
#include <zui/zuiutils.h>
#include <zui/zuiplugin.h>
#include <zui/zuiplugininterface.h>

using namespace std;


/*!
  \class ZuiParser
  \ingroup zui
  \brief Parses a ZUI definition file and dynamically builds the user interface.

  Zee can interact with users via a GUI, if so desired, via a highly-
  configurable system called ZUI.  ZUI is comprised of plugins that define sets
  of widgets that provide certain functionality.  The configuration of the
  overall application is controlled via an \ref zui-def "XML UI definition file".
  As plugins are loaded, new elements are made available to the XML definition
  for inclusion in the application's interface.

  \section zui-def        ZUI Definition File

  \section zui-plugins    Plugins
*/
class ZuiParser : public QObject
{
  Q_OBJECT

  private:
    Zee *_parent;
    QWidget *_currentParent;
    ZConfigurable::ZConfig _config;
    int depth;
    QList<ZcmPluginInterface*> zcmModules;
    QList<ZuiPluginInterface*> zuiModules;
  public:
/*!
  Constructs a new parser object, using \a rootNode as the entry point for
  parsing an XML definition file.  The output of this parsing effort, which is
  dictated by widgetes created in one or more plugins, is parented at
  \a destWidget.
*/
    ZuiParser(QDomElement &el);

  private:
/*!
  \internal

  Initializes the class
*/
    void init();


/*!
  Dynamically loads modules (as Qt Plugins) that will enable
  certain features and widget sets in the ZML definition.

  \todo pull a configuration of modules to load (and where from) out of the ZML
*/
    void loadModules();


/*!
  Parses the XML DOM object at \a rnode, operating recursively on any child
  element nodes present.

  This recursive method sequentially builds the UI components from the XML
  definition file.
*/
    void parse(QDomNode &n);


/*!
  Parses \a node, passing it to all loaded plugins (in the order in which they
  were loaded).  Each plugin may or may not create a new widget to be added to
  the current parent widget.
*/
    bool parseNode(QDomNode &node);


/*!
  Parses \a node, looking for elements that are part of the core system
*/
    void prepareWidget(const QDomElement &el);


/*!
  Perform the insertion of \a cWidget as a child of \a cParent, parsing any
  extra information needed from \a el.  This includes setup common to all
  widgets; including event handling, base attributes, and actually adding the
  new widget to the parent layout.
*/
    bool pushWidget(QDomElement&, QWidget *cWidget, QWidget *cParent);
};

#endif
