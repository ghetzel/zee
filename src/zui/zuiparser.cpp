#include "zuiparser.h"

ZuiParser::ZuiParser(QDomElement &el)
{
    //init basic variables
    _config = el;
    depth = 0;
    _currentParent = NULL;

    init();

    //parse(_config);
    //parse(el);
    QDomNodeList nn;

    nn = _config.elementsByTagName("zee:components");
    for(uint i = 0; i < nn.length(); i++)
        parse(nn.item(i));

    nn = _config.elementsByTagName("zee:widgets");
    for(uint i = 0; i < nn.length(); i++)
        parse(nn.item(i));

    nn = _config.elementsByTagName("zee:events");
    for(uint i = 0; i < nn.length(); i++)
        parse(nn.item(i));


    if(qApp->topLevelWidgets().count() == 0)
	z_log_warn("ZuiParser: No widgets added");
}


void ZuiParser::init()
{
    loadModules();
}

void ZuiParser::loadModules(){
    QDir zModulesDir = QDir(qApp->applicationDirPath());

#if defined(Q_OS_WIN)
    if (zModulesDir.dirName().toLower() == "debug" || zModulesDir.dirName().toLower() == "release")
	zModulesDir.cdUp();
#endif

    zModulesDir.cd("plugins");

    //for each module in <approot>/plugins/zui/...
    foreach(QString modFile, zModulesDir.entryList(QDir::Files)){
	QPluginLoader loader(zModulesDir.absoluteFilePath(modFile));
	QObject *module = loader.instance();

	if(module){
	    // ZCM?
            ZcmPluginInterface *iZcmMod = QCAST(ZcmPluginInterface*,module);
	    // ZUI?
            ZuiPluginInterface *iZuiMod = QCAST(ZuiPluginInterface*,module);

	    if(iZuiMod){
		zuiModules << iZuiMod;
		z_log("ZuiParser: Loaded ZUI module '"+modFile+"'");
	    }else if(iZcmMod){
		zcmModules << iZcmMod;
		z_log("ZuiParser: Loaded ZCM module '"+modFile+"'");
	    }
	}else{
	    //    output the error that occurred
	    z_log_error("Error loading "+modFile+": "+loader.errorString());
	}
    }

    foreach(ZcmPluginInterface *m, zcmModules)
	m->initialize(zEvent);
    foreach(ZuiPluginInterface *m, zuiModules){
	m->initialize(zEvent);
	ZuiUtils::registerContainerElements(m->getContainerNames());
    }
}


void ZuiParser::parse(QDomNode n)
{
    //attempt to find the first child
    QDomNode node = n.firstChild();

    //	while there are siblings to process...
    while(!node.isNull())
    {
	//  add the proper widget to the tree
	parseNode(node);

	//  continue down the chain
	if(node.hasChildNodes())
	    parse(node);

	//   move the _currentParent that new widgets will be added to back up
	//   the chain if this node is a container.  by this point, all of its
	//   child nodes will have been added to the widget, so we can safely
	//   move back up to prepare to process the next sibling
	//
	//   if is a container node...
	//   	if the container node has a parent set (always should)
	//   		set parent = current parent's parent
	if(ZuiUtils::getContainerNames().contains(node.nodeName()))
	    if(_currentParent && _currentParent->parent() != NULL){
	    _currentParent = CAST(QWidget*,_currentParent->parent());
	    --depth;
	}


	//  move onto the next sibling
	node = node.nextSibling();
    }
}


bool ZuiParser::parseNode(QDomNode &node)
{
    //attempt to convert the node to an element
    QDomElement el = node.toElement();
    ZuiResult zResult = {NULL,NULL};

    //if the node was element-able...
    if(!el.isNull())
    {
	QString elns = el.tagName().section(":",0,0);

	if(elns == "zui"){
	    //  for each ZUI plugin...
	    //  call the module's prepareWidget() method; if it
	    //  returns true, break; else, move on.  Ideally, (at least) one of the
	    //  prepareWidget calls would result in a true (meaning that the node was
	    //  matched, and the preparation logic was run).  Failing that, currentWidget
	    //  will remain NULL and nothing will happen.
	    foreach(ZuiPluginInterface *mod, zuiModules){
		zResult.widget = NULL;
		zResult.parent = NULL;

		zResult = mod->prepareWidget(el, _currentParent);

		//    if there is a new widget...
		if(zResult.widget){
		    _currentParent = zResult.parent;
		    break;
		}
	    }

	    //  connect handlers, set properties, and display the widget
	    pushWidget(el, zResult.widget, zResult.parent);
	}else if(elns == "zee"){
	    ZcmResult zcmres;
	    foreach(ZcmPluginInterface *mod, zcmModules){
		zcmres = mod->prepare(el);
	    }
	}

	//  do local processing
	prepareWidget(el);
    }

    return true;
}

void ZuiParser::prepareWidget(const QDomElement &el){
    if(el.tagName() == "zee:connect"){
	if(el.hasAttribute("from") &&
	   el.hasAttribute("to"))
	{
	    zEvent->map(el.attribute("from"),
			el.attribute("to"),
			el.attribute("via"),
			QVariant(el.attribute("direct","true")).toBool());
	}
    }
}


bool ZuiParser::pushWidget(QDomElement&, QWidget *cWidget, QWidget *cParent)
{

    QWidget *cWidgetParent = NULL;

    if(cWidget && cParent){
	//    finally, add the widget to the hierarchy...
	//    if the current widget is the new parent widget,
	//    go to *its* parent and add it to that layout
	//    (otherwise you'll try adding the widget to its own
	//    layout, infiniloop)
	if(cWidget == cParent){
            if(cParent->parent()){
                cWidgetParent = CAST(QWidget*,cParent->parent());

                if(cWidgetParent->layout())
                    cWidgetParent->layout()->addWidget(cWidget);
            }
	    ++depth;
	}else{
	    cParent->layout()->addWidget(cWidget);
	}

	return true;
    }

    return false;
}
