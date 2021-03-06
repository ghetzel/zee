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

#ifndef ZTUPLELISTMODEL_H
#define ZTUPLELISTMODEL_H

#include <QAbstractListModel>
#include <QIcon>
#include <zutil.h>

class ZTupleListModel : public QAbstractListModel
{
public:
    ZTupleListModel(QObject *parent=0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
			int role = Qt::DisplayRole) const;
    void appendRow(QString text, QVariant data);

private:
    struct ZListTuple{
	QIcon decoration;
	QString display;
	QVariant data;
    };

    QList<ZListTuple> _items;
};

#endif // ZTUPLELISTMODEL_H
