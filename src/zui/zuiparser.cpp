/******************************************************************************
*    This file is part of Zee.
*
*    Zee is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    Zee is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with Zee.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#include "zuiparser.h"

ZuiParser::ZuiParser(QDomElement &el, ZCoreApplication *parent)
{
    //init basic variables
    _parent = parent;
    _config = ZConfig(el);
    depth = 0;
    _currentParent = NULL;

    init();

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

//  late component initialize
    foreach(QObject *c, _components){
        ZConfigurable *cmp = DCAST(ZConfigurable*,c);
        Q_ASSERT(cmp);
        cmp->lateInit();
    }

//  late widget initialize
    foreach(QWidget *w, qApp->allWidgets()){
        ZConfigurable *cmp = DCAST(ZConfigurable*,w);
        if(cmp)
            cmp->lateInit();
    }


    if(qApp->topLevelWidgets().count() == 0)
        z_log_warn("ZuiParser: No widgets added");

    z_log("ZuiParser: **Configuration Parsing Complete**");
}


void ZuiParser::init()
{
    loadModules();
}

void ZuiParser::loadModules(){
    QDir zModulesDir;

    if(_parent && _parent->hasArg("prefix"))
        zModulesDir.setPath(_parent->arg("prefix").toString());
    else
        zModulesDir.setPath(qApp->applicationDirPath());

    zModulesDir.cd("plugins");

    //for each module in <prefix>/plugins/zui/...
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

    foreach(ZuiPluginInterface *m, zuiModules)
        m->initialize(zEvent);
}


void ZuiParser::parse(ZConfigNode n)
{
    //attempt to find the first child
    ZConfigNode node = n.firstChild();

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
        if(DCAST(ZContainerWidget*,node.object())){
            if(_currentParent && _currentParent->parent() != NULL){
                _currentParent = CAST(QWidget*,_currentParent->parent());
                --depth;
            }
        }

        //  move onto the next sibling
        node = node.nextSibling();
    }
}


bool ZuiParser::parseNode(ZConfigNode &node)
{
    //attempt to convert the node to an element
    QDomElement el = node.toElement();
    ZuiResult zResult;
    _currentWidget = NULL;

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
                zResult = mod->prepareWidget(el, _currentParent);

                //    if there is a new widget...
                if(zResult.widget){
                    node.setObject(zResult.widget);
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

                if(zcmres.component){
                    _components << zcmres.component;
                    break;
                }
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
                        el.attribute("formatter"),
                        QVariant(el.attribute("direct","true")).toBool());
        }
    }
}


bool ZuiParser::pushWidget(QDomElement &el, QWidget *cWidget, QWidget *cParent)
{

    QWidget *cWidgetParent = NULL;
    QLayout *targetLayout = NULL;

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
                    targetLayout = cWidgetParent->layout();
            }
            ++depth;
        }else{
            targetLayout = cParent->layout();
        }

        if(targetLayout){
            QDomElement elp = el.parentNode().toElement();
            if(!elp.isNull()){
            //  make sure we have a layout directive
                if(elp.tagName() == "zui:layout"){
                //  Border Layout
                //  Ex.:
                //        <zui:container layout="border">
                //            <zui:layout side="north">
                //                ... NORTH WIDGETS ...
                //            </zui:layout>
                //            <zui:layout side="east">
                //                ... EAST WIDGETS ...
                //            </zui:layout>
                //
                //            <zui:layout>
                //                ... CENTER WIDGETS ...
                //            </zui:layout>
                //        </zui:container>
                //
                    if(DCAST(ZBorderLayout*,targetLayout)){
                        ZBorderLayout *lom = DCAST(ZBorderLayout*,targetLayout);

                    //  specifies side of border layout to insert into
                        if(elp.hasAttribute("side")){
                            if(ZuiUtils::attribute(elp.attribute("side"),ZuiUtils::CardinalNorth)){       // North
                                lom->addWidget(cWidget, ZBorderLayout::North);
                            }else if(ZuiUtils::attribute(elp.attribute("side"),ZuiUtils::CardinalSouth)){ // South
                                lom->addWidget(cWidget, ZBorderLayout::South);
                            }else if(ZuiUtils::attribute(elp.attribute("side"),ZuiUtils::CardinalEast)){ // East
                                lom->addWidget(cWidget, ZBorderLayout::East);
                            }else if(ZuiUtils::attribute(elp.attribute("side"),ZuiUtils::CardinalWest)){ // West
                                lom->addWidget(cWidget, ZBorderLayout::West);
                            }else{                                  // Center
                                z_log_debug("ZuiParser: Border Center Count = "+STR(lom->count(ZBorderLayout::Center)));
                                lom->addWidget(cWidget, ZBorderLayout::Center);
                            }
                        }else{                                      // Fallback
                            lom->addWidget(cWidget, ZBorderLayout::Center);
                        }
                    }else if(DCAST(QGridLayout*,targetLayout)){
                        QGridLayout *lom = DCAST(QGridLayout*,targetLayout);

                        if(elp.hasAttribute("cell")){
                            QStringList elcell = elp.attribute("cell").split(",");
                            if(elcell.length() == 2){
                                QPoint cell(elcell.value(1).toInt(),
                                            elcell.value(0).toInt());

                                lom->addWidget(cWidget, cell.y(), cell.x(),
                                               elp.attribute("rowspan","1").toInt(),
                                               elp.attribute("colspan","1").toInt(),
                                               ZuiUtils::getAlignment(elp.attribute("align")));
                            }
                        }
                    }
                }else{
                    targetLayout->addWidget(cWidget);
                }
            }
        }

        return true;
    }

    return false;
}
