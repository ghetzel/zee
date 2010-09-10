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

#include "zlistwidgetitem.h"

ZListWidgetItem::ZListWidgetItem(QListWidget *parent, int type)
  : QListWidgetItem(parent, type){
}

ZListWidgetItem::ZListWidgetItem(const QString &text,
		QListWidget *parent,
		int type)
		  : QListWidgetItem(text, parent, type){

}

ZListWidgetItem::ZListWidgetItem(const QIcon &icon,
		const QString &text,
		QListWidget *parent,
		int type)
		  : QListWidgetItem(icon, text, parent, type){

}

ZListWidgetItem::ZListWidgetItem(const QListWidgetItem &other)
  : QListWidgetItem(other){

}

void ZListWidgetItem::setPayload(int key, QVariant data){
  _payload.insert(key, data);
}

QVariant ZListWidgetItem::payload(int key){
  return _payload.value(key);
}
