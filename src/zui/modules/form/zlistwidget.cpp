#include "zlistwidget.h"

ZListWidget::ZListWidget(const ZConfig &el, QWidget *parent)
    : ZWidget<QListView>(el,this,parent)
{
    connect(this, SIGNAL(activated(QModelIndex)),
	    this, SLOT(_activated(QModelIndex)));
    parse(_config);
    zEvent->registerSignal(this, SIGNAL(activated(QVariant)));
    zEvent->registerSignal(this, SIGNAL(selected(QVariant)));
    zEvent->registerSlot(this, SLOT(setCurrentIndex(int)));
    zEvent->registerSlot(this, SLOT(setCurrentIndex(QModelIndex)));
}


void ZListWidget::parse(const ZConfig &el){
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

    if(el.attribute("view","list") == "list")
        setViewMode(QListView::ListMode);
    else
        setViewMode(QListView::IconMode);

    if(el.hasAttribute("grid")){
      QStringList gridWH = el.attribute("grid","32x32").split("x");
      int gW = QString(gridWH.first()).toInt();
      int gH = QString(gridWH.last()).toInt();
      setGridSize(QSize(gW,gH));
    }

    QStringList icosz = el.attribute("icons","16x16").split("x");
    int iW = icosz.first().toInt();
    int iH = icosz.last().toInt();
    setIconSize(QSize(iW,iH));

    setEditTriggers(0);

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

void ZListWidget::currentChanged(const QModelIndex &current,
                                 const QModelIndex &previous)
{
    z_log_debug("ZListWidget: Selected "+current.data(Qt::UserRole+1).toString());
    if(current.data(Qt::UserRole+1).isValid())
        emit selected(current.data(Qt::UserRole+1));
    QListView::currentChanged(current,previous);
}
