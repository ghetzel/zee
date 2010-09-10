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

#ifndef ZLISTWIDGETITEM_H
#define ZLISTWIDGETITEM_H

#include <QtCore>
#include <QtGui>

class ZListWidgetItem : public QListWidgetItem
{

public:
  ZListWidgetItem(QListWidget *parent = 0, int type = Type);
  ZListWidgetItem(const QString &text,
		  QListWidget *parent = 0,
		  int type = Type);
  ZListWidgetItem(const QIcon &icon,
		  const QString &text,
		  QListWidget *parent = 0,
		  int type = Type);
  ZListWidgetItem(const QListWidgetItem &other);
  void setId(QVariant id){ _id = id; }
  QVariant id(){ return _id; }
  void setPayload(int key, QVariant data);
  QVariant payload(int key);

private:
  QVariant _id;
  QHash<int,QVariant> _payload;

};

#endif // ZLISTWIDGETITEM_H
