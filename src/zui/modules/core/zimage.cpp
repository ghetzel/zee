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

#include "zimage.h"

ZImage::ZImage(const ZConfig &el, QWidget *parent)
    : QLabel(parent),
      ZWidget(el,this){
    parse(_config);
}

void ZImage::parse(const ZConfig &el){
//! @src - the path to an image file
    if(el.hasAttribute("src")){
        setImage(el.attribute("src"));

//! @icon - the path or system name of an icon
    }else if(el.hasAttribute("icon")){
        setIcon(el.attribute("icon"));
    }

//! @align - the alignment of the image
    if(el.hasAttribute("align"))
        setAlignment(ZuiUtils::getAlignment(el.attribute("align")));
    else
        setAlignment(Qt::AlignCenter);

}

void ZImage::setIcon(QString name){
    _icon = ZuiUtils::getIcon(name);

    if(!_icon.isNull())
        setPixmap(_icon.pixmap(width(), height(), QIcon::Normal));
}

QString ZImage::icon() const{
    return _iconName;
}

void ZImage::setImage(QString name){
    z_log_debug("ZImage: "+name);
    if(QFile::exists(name)){
        _imagePath = name;
        setPixmap(name);
    }
}

QString ZImage::image() const{
    return _imagePath;
}
