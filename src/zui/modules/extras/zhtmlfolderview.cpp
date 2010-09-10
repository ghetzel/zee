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

#include "zhtmlfolderview.h"

ZHTMLFolderView::ZHTMLFolderView(const ZConfig &el, QWidget *parent)
    : ZListWidget(el,parent)
{
    parse(_config);
    init();
}

void ZHTMLFolderView::parse(const ZConfig &el){
    if(el.hasAttribute("uri")){
	_model = new ZHTMLListModel(QUrl::fromUserInput(el.attribute("uri")),
				    this);
	setModel(_model);
    }
}

void ZHTMLFolderView::init(){
    zEvent->registerSlot(this, SLOT(setUrl(QString)));
}

void ZHTMLFolderView::setUrl(QString location){
    if(_model){
	_model->setBaseUrl(QUrl::fromUserInput(location));
    }
}
