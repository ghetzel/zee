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

#include "ztuplelistmodel.h"

ZTupleListModel::ZTupleListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int ZTupleListModel::rowCount(const QModelIndex&) const{
    return _items.count();
}

QVariant ZTupleListModel::data(const QModelIndex &index, int role) const{
    if(!index.isValid())
	return QVariant();
    if(index.row() >= _items.size())
	return QVariant();

    switch(role){
    case Qt::DisplayRole:
	return _items.at(index.row()).display;
    case Qt::UserRole:
	return _items.at(index.row()).data;
    }

    return QVariant();
}

QVariant ZTupleListModel::headerData(int section, Qt::Orientation orientation,
				     int role) const
{
    if(role != Qt::DisplayRole)
	return QVariant();
    if(orientation == Qt::Horizontal)
	return QString("C%1").arg(section);
    else
	return QString("R%1").arg(section);
}

void ZTupleListModel::appendRow(QString text, QVariant data){
    //z_log_debug("ZTupleListModel: "+text+"="+data.toString());
    ZListTuple d;
    d.data = data;
    d.display = text;
    _items.append(d);
}
