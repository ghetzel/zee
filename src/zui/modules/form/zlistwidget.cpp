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

#include "zlistwidget.h"

ZListWidget::ZListWidget(const ZConfig &el, QWidget *parent)
    : QListView(parent),
      ZWidget(el,this)
{
    connect(this, SIGNAL(activated(QModelIndex)),
            this, SLOT(_activated(QModelIndex)));
    connect(this, SIGNAL(clicked(QModelIndex)),
            this, SLOT(_clicked(QModelIndex)));
    connect(this, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(_doubleClicked(QModelIndex)));

    parse(_config);
    zEvent->registerSignal(this, SIGNAL(activated(QVariant)));
    zEvent->registerSignal(this, SIGNAL(selected(QVariant)));
    zEvent->registerSignal(this, SIGNAL(clicked(QVariant)));
    zEvent->registerSignal(this, SIGNAL(doubleClicked(QVariant)));
    zEvent->registerSlot(this, SLOT(setCurrentIndex(int)));
    zEvent->registerSlot(this, SLOT(setCurrentIndex(QModelIndex)));
}


void ZListWidget::parse(const ZConfig &el){
//! @scroll (hidden|scroll|auto) - the display policy for scrollbars
    if(el.hasAttribute("scroll"))
    {
      if(el.attribute("scroll") == "hidden"){
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
      }else if(el.attribute("scroll") == "scroll"){
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
      }
    }

/*! @select (multi|extended|single|contiguous|none) - the selection policy for
        items.

        #multi      - allow multiple random selections
        #extended   - ???
        #single     - allow a single item to be selected
        #contiguous - allow multiple adjacent items to be selected
        #none       - prevent item selection
  */
    if(el.hasAttribute("select")){
        if(el.attribute("select") == "multi")
            setSelectionMode(QAbstractItemView::MultiSelection);
        else if(el.attribute("select") == "extended")
            setSelectionMode(QAbstractItemView::ExtendedSelection);
        else if(el.attribute("select") == "single")
            setSelectionMode(QAbstractItemView::SingleSelection);
        else if(el.attribute("select") == "contiguous")
            setSelectionMode(QAbstractItemView::ContiguousSelection);
        else if(el.attribute("select") == "none")
            setSelectionMode(QAbstractItemView::NoSelection);
    }

//! @view (list|icon) - the manner in which items are displayed
    if(el.attribute("view","list") == "list")
        setViewMode(QListView::ListMode);
    else
        setViewMode(QListView::IconMode);

//! @grid - the size of the icon arrangement grid (format: ##x##)
    if(el.hasAttribute("grid")){
      QStringList gridWH = el.attribute("grid","32x32").split("x");
      int gW = QString(gridWH.first()).toInt();
      int gH = QString(gridWH.last()).toInt();
      setGridSize(QSize(gW,gH));
    }

//! @icons - the size of the icons (format: ##x##)
    QStringList icosz = el.attribute("icons","16x16").split("x");
    int iW = icosz.first().toInt();
    int iH = icosz.last().toInt();
    setIconSize(QSize(iW,iH));

    setEditTriggers(0);

//! @flow (vertical|horizontal) - the direction icon items flow in
    if(el.attribute("flow","vertical") == "vertical")
      setFlow(QListView::TopToBottom);
    else
      setFlow(QListView::LeftToRight);

    if(el.hasChildNodes()){
        QDomNodeList items = el.childNodes();
        QStandardItemModel *m = new QStandardItemModel(0,1,this);
        QDomNode item;
        QDomElement iel;

        for(int i = 0; i < items.count(); i++){
            item = items.at(i);
            if(item.isElement()){
                iel = item.toElement();
                if(iel.tagName() == ZLIST_ITEM_NAME){
                    QStandardItem *i = new QStandardItem();
                    i->setData(iel.attribute("value"));
                    i->setData(iel.text(), Qt::DisplayRole);
                    i->setData(ZuiUtils::getIcon(iel.attribute("icon","")),
                               Qt::DecorationRole);
                    z_log_debug("ZListWidget: Adding Item "+iel.text()+", ico = "+QVariant(i->icon().isNull()).toString());
                    m->appendRow(i);
                }
            }
        }

        setModel(m);

//! @model - object path to the data model
    }else if(el.hasAttribute("model")){
        QObject *target = zEvent->findObject(el.attribute("model"),true);

        if(!target)
            z_log_error("ZListWidget: Object '"+el.attribute("model")+"' not found");

        QAbstractItemModel *model = QCAST(QAbstractItemModel*,target);
        if(model)
            setModel(model);
        else
            z_log_error("ZListWidget: Object '"+el.attribute("model")+"' is"
                        " not a model!");
    }
}

void ZListWidget::setCurrentIndex(int row){
    if(model())
        QListView::setCurrentIndex(model()->index(row,0));
}


void ZListWidget::_activated(QModelIndex i){
    if(i.data(Qt::UserRole+1).isValid()){
        z_log_debug("ZListWidget: Activated "+i.data(Qt::UserRole+1).toString());
        emit activated(i.data(Qt::UserRole+1));
    }
}

void ZListWidget::_clicked(QModelIndex i){
    if(i.data(Qt::UserRole+1).isValid()){
        z_log_debug("ZListWidget: Clicked "+i.data(Qt::UserRole+1).toString());
        emit clicked(i.data(Qt::UserRole+1));
    }
}

void ZListWidget::_doubleClicked(QModelIndex i){
    if(i.data(Qt::UserRole+1).isValid()){
        z_log_debug("ZListWidget: Double Clicked "+i.data(Qt::UserRole+1).toString());
        emit doubleClicked(i.data(Qt::UserRole+1));
    }
}

void ZListWidget::currentChanged(const QModelIndex &current,
                                 const QModelIndex &previous)
{
    z_log_debug("ZListWidget: Selected "+current.data(Qt::UserRole+1).toString());
    if(current.data(Qt::UserRole+1).isValid())
        emit selected(current.data(Qt::UserRole+1));
    QListView::currentChanged(current,previous);
}
