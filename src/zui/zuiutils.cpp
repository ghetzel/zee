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

#include "zuiutils.h"

QList<QString> ZuiUtils::_containers;

void ZuiUtils::initialize(){
}

void ZuiUtils::registerContainerElement(QString tagName)
{
  if(!_containers.contains(tagName))
    _containers.append(tagName);
}

void ZuiUtils::registerContainerElements(QList<QString> elements)
{
  foreach(QString element, elements)
    if(!_containers.contains(element))
      _containers.append(element);
}

QList<QString> ZuiUtils::getContainerNames()
{
  return _containers;
}

QLayout *ZuiUtils::getLayout(QString id)
{
  QLayout *layout = NULL;

//	determine layout manager to install
  if(id == ZUI_HORIZON_LAYOUT){                 // horizontal layout
    layout = new QHBoxLayout;
  }else if(id == ZUI_VERTICAL_LAYOUT){          // vertical layout
    layout = new QVBoxLayout;
  }else if(id == ZUI_GRID_LAYOUT){		// grid layout
    layout = new QGridLayout;
  }else if(id == ZUI_FORM_LAYOUT){		// form layout
    layout = new QFormLayout;
  }else if(id == ZUI_FLOW_LAYOUT){              // flow layout
    layout = new ZFlowLayout;
  }else if(id == ZUI_BORDER_LAYOUT){            // border layout
    layout = new ZBorderLayout;
  }else{
    layout = new ZUI_FAILOVER_LAYOUT;
  }

  layout->setContentsMargins(0,0,0,0);
  layout->setSpacing(0);
  return layout;
}


QIcon ZuiUtils::getIcon(QString name){
    if(QFile::exists(name))
	return QIcon(name);
    else
	return QIcon::fromTheme(name);
}

void ZuiUtils::prepareContainer(QWidget *newWidget, const QDomElement *el){
  newWidget->setLayout(ZuiUtils::getLayout(
    el->attribute("layout", ZUI_DEFAULT_LAYOUT)));

  if(el->hasAttribute("align")){
    if(el->attribute("align") == "right"){
      //newWidget->setLayoutDirection(Qt::RightToLeft);
    }
  }
}

bool ZuiUtils::attributeTrue(QDomElement el, QString name){
    return (el.hasAttribute(name) && QVariant(el.attribute(name)).toBool());
}

bool ZuiUtils::attributeFalse(QDomElement el, QString name){
    return !ZuiUtils::attributeTrue(el,name);
}

bool ZuiUtils::attributeEquals(QDomElement el, QString name, QVariant match){
    return (el.hasAttribute(name) && el.attribute(name) == match.toString());
}
