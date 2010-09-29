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

#include "ztableview.h"

ZTableView::ZTableView(const ZConfig &el, QWidget *parent)
    : QTableView(parent),
      ZWidget(el,this)
{
    parse(_config);
}

void ZTableView::parse(const ZConfig &el){
//! @model - the object path to the data model
    if(el.hasAttribute("model")){
	QObject *target = zEvent->findObject(el.attribute("model"),true);

	if(!target)
	    z_log_error("ZTableView: Object '"+el.attribute("model")+"' not found");

	QAbstractItemModel *model = QCAST(QAbstractItemModel*,target);
	if(model)
	    setModel(model);
	else
	    z_log_error("ZTableView: Object '"+el.attribute("model")+"' is"
			" not a model!");
    }
}
