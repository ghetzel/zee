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

#ifndef ZLIST_WIDGET_
#define ZLIST_WIDGET_

#define ZUI_LIST            "zui:list"
#define ZLIST_ITEM_NAME     "zui:item"

#include <iostream>
#include <QListView>
#include <QtCore>
#include <zutil.h>
#include <zui/zuiutils.h>
#include <zui/zwidget.h>
#include "ztuplelistmodel.h"

using namespace std;

/*!
  \class ZListWidget
  \ingroup zui_plugins_form
  \brief A list
*/
class ZListWidget : public QListView, public ZWidget
{
    Q_OBJECT

public:
    ZListWidget(const ZConfig &el, QWidget *parent);

signals:
    void activated(QVariant);
    void selected(QVariant);
    void clicked(QVariant);
    void doubleClicked(QVariant);

public slots:
    void setCurrentIndex(int row);

private slots:
    void _activated(QModelIndex i);
    void _clicked(QModelIndex i);
    void _doubleClicked(QModelIndex i);

private:
    void parse(const ZConfig &el);
    void currentChanged(const QModelIndex &current, const QModelIndex &previous);
};

#endif
