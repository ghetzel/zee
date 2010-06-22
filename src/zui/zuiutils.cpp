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
  if(id == ZUI_HORIZON_LAYOUT){		// horizontal layout
    layout = new QHBoxLayout;
  }else if(id == ZUI_VERTICAL_LAYOUT){	// vertical layout
    layout = new QVBoxLayout;
  }else if(id == ZUI_GRID_LAYOUT){		// grid layout
    layout = new QGridLayout;
  }else if(id == ZUI_FORM_LAYOUT){		// form layout
    layout = new QFormLayout;
  }else if(id == ZUI_FLOW_LAYOUT){
    layout = new ZFlowLayout;
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
