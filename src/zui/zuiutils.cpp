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

bool ZuiUtils::attribute(QString source, ZConfigAttribOption option){
    if(source.isEmpty())
        return false;

//  normalize source string
    source = source.toLower();
    source = source.remove(QRegExp("[-_ ]"));

    switch(option){
    case AlignBottom:
        return ZUtil::in(source, ZCONFIG_ATTRIB_ALIGN_BOTTOM);
    case AlignCenter:
        return ZUtil::in(source, ZCONFIG_ATTRIB_ALIGN_CENTER);
    case AlignHCenter:
        return ZUtil::in(source, ZCONFIG_ATTRIB_ALIGN_HCENTER);
    case AlignJustify:
        return ZUtil::in(source, ZCONFIG_ATTRIB_ALIGN_JUSTIFY);
    case AlignLeft:
        return ZUtil::in(source, ZCONFIG_ATTRIB_ALIGN_LEFT);
    case AlignRight:
        return ZUtil::in(source, ZCONFIG_ATTRIB_ALIGN_RIGHT);
    case AlignTop:
        return ZUtil::in(source, ZCONFIG_ATTRIB_ALIGN_TOP);
    case AlignVCenter:
        return ZUtil::in(source, ZCONFIG_ATTRIB_ALIGN_VCENTER);
    case BooleanFalse:
        return ZUtil::in(source, ZCONFIG_ATTRIB_BOOL_FALSE);
    case BooleanTrue:
        return ZUtil::in(source, ZCONFIG_ATTRIB_BOOL_TRUE);
    case CardinalEast:
        return ZUtil::in(source, ZCONFIG_ATTRIB_CARD_E);
    case CardinalNorth:
        return ZUtil::in(source, ZCONFIG_ATTRIB_CARD_N);
    case CardinalNorthEast:
        return ZUtil::in(source, ZCONFIG_ATTRIB_CARD_NE);
    case CardinalNorthWest:
        return ZUtil::in(source, ZCONFIG_ATTRIB_CARD_NW);
    case CardinalSouth:
        return ZUtil::in(source, ZCONFIG_ATTRIB_CARD_S);
    case CardinalSouthEast:
        return ZUtil::in(source, ZCONFIG_ATTRIB_CARD_SE);
    case CardinalSouthWest:
        return ZUtil::in(source, ZCONFIG_ATTRIB_CARD_SW);
    case CardinalWest:
        return ZUtil::in(source, ZCONFIG_ATTRIB_CARD_W);
    case SeverityCritical:
        return ZUtil::in(source, ZCONFIG_ATTRIB_SEV_CRIT);
    case SeverityDebug:
        return ZUtil::in(source, ZCONFIG_ATTRIB_SEV_DEBUG);
    case SeverityError:
        return ZUtil::in(source, ZCONFIG_ATTRIB_SEV_ERROR);
    case SeverityInfo:
        return ZUtil::in(source, ZCONFIG_ATTRIB_SEV_INFO);
    case SeverityQuestion:
        return ZUtil::in(source, ZCONFIG_ATTRIB_SEV_QUESTION);
    case SeverityWarning:
        return ZUtil::in(source, ZCONFIG_ATTRIB_SEV_WARN);
    case RadialDirectionClockwise:
        return ZUtil::in(source, ZCONFIG_ATTRIB_RAD_CLOCK);
    case RadialDirectionCounterClockwise:
        return ZUtil::in(source, ZCONFIG_ATTRIB_RAD_CNTCLOCK);
    }

    return false;
}

Qt::Alignment ZuiUtils::getAlignment(QString configVal){
    Qt::Alignment retval = 0;
    QStringList cvs = configVal.split(QRegExp("\\W+"));

    foreach(QString cv, cvs)
        if(ZuiUtils::attribute(cv,ZuiUtils::AlignLeft))
            retval |= Qt::AlignLeft;
        else if(ZuiUtils::attribute(cv,ZuiUtils::AlignRight))
            retval |= Qt::AlignRight;
        else if(ZuiUtils::attribute(cv,ZuiUtils::AlignCenter))
            retval |= Qt::AlignCenter;
        else if(ZuiUtils::attribute(cv,ZuiUtils::AlignJustify))
            retval |= Qt::AlignJustify;
        else if(ZuiUtils::attribute(cv,ZuiUtils::AlignHCenter))
            retval |= Qt::AlignHCenter;
        else if(ZuiUtils::attribute(cv,ZuiUtils::AlignVCenter))
            retval |= Qt::AlignVCenter;
        else if(ZuiUtils::attribute(cv,ZuiUtils::AlignTop))
            retval |= Qt::AlignTop;
        else if(ZuiUtils::attribute(cv,ZuiUtils::AlignBottom))
            retval |= Qt::AlignBottom;

    return retval;
}


QIcon ZuiUtils::getIcon(QString name){
    if(QFile::exists(name))
        return QIcon(name);
    else
        return QIcon::fromTheme(name);
}

bool ZuiUtils::attributeTrue(QString value){
    return ZuiUtils::attribute(value, ZuiUtils::BooleanTrue);
}

bool ZuiUtils::attributeFalse(QString value){
    return ZuiUtils::attribute(value, ZuiUtils::BooleanFalse);
}

bool ZuiUtils::attributeEquals(QDomElement el, QString name, QVariant match){
    return (el.hasAttribute(name) && el.attribute(name) == match.toString());
}
