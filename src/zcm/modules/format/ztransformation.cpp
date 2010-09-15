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

#include "ztransformation.h"

ZTransformation::ZTransformation(const ZConfig &el, QObject *parent)
    : QObject(parent),
      ZConfigurable(el,this)
{
    parse(_config);
}

void ZTransformation::parse(const ZConfig &el){
    QDomNodeList elc = el.childNodes();
    QDomElement elfmt;

    for(int i = 0; i < elc.length(); i++){
        elfmt = elc.at(i).toElement();
        if(elfmt.tagName() == ZCM_FORMATTER){
            _formatters << new ZFormatter(elfmt,this);
        }
    }
}

//void ZTransformation::chainFormatters(){
//    if(!_formatters.isEmpty()){
//        connect(this, SIGNAL(start(QVariant)),
//                _formatters.first(), SLOT(transform(QVariant)));
//
//        foreach(ZFormatter *formatter, _formatters){
//            connect(formatter, SIGNAL(ready(QVariant)),
//                    //next,   transform())
//        }
//    }
//}

void ZTransformation::transform(QVariant val){
    emit start(val);
}
