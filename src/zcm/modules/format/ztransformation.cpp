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
    : ZFormatterInterface(parent),
      ZConfigurable(el,this)
{
    parse(_config);

    zEvent->registerSignal(this, SIGNAL(ready(QVariant)));
    zEvent->registerSlot(this, SLOT(transform(QVariant)));
}

void ZTransformation::parse(const ZConfig &el){
    QDomNodeList elc = el.childNodes();
    QDomElement elfmt;

    for(uint i = 0; i < elc.length(); i++){
        elfmt = elc.at(i).toElement();
        if(elfmt.tagName() == ZTRANS_FORMATTER){
            elfmt.setAttribute("id", objectName()+"_formatter"+QString(i));
            _formatters << new ZFormatter(elfmt,this);
        }
    }

    chainFormatters();
}

void ZTransformation::chainFormatters(){
//    if(!_formatters.isEmpty()){
//	connect(this, SIGNAL(start(QVariant)),
//		_formatters.first(), SLOT(transform(QVariant)));
//
//	for(int i = 0; i < _formatters.length(); i++){
//	    if(_formatters.at(i) == _formatters.last()){
//		connect(_formatters.at(i), SIGNAL(ready(QVariant)),
//			this, SIGNAL(ready(QVariant)));
//	    }else{
//		connect(_formatters.at(i), SIGNAL(ready(QVariant)),
//			_formatters.at(i+1), SLOT(transform(QVariant)));
//	    }
//	}
//    }
}

QVariant ZTransformation::transform(QVariant val){
    return val;
}

void ZTransformation::setParam(QString key, QVariant value){

}
