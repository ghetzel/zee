#include "zlistwidget.h"

ZListWidget::ZListWidget(const ZConfig &el, QWidget *parent)
    : QListView(parent),
      ZWidget(el,this)
{
    connect(this, SIGNAL(activated(QModelIndex)),
	    this, SLOT(_activated(QModelIndex)));
    parse(_config);
    zEvent->registerSignal(this, SIGNAL(activated(QVariant)));
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

    if(el.attribute("flow","vertical") == "vertical")
      setFlow(QListView::TopToBottom);
    else
      setFlow(QListView::LeftToRight);

    if(el.hasChildNodes()){
        ZTupleListModel *m = new ZTupleListModel(this);
        QDomNodeList items = el.childNodes();
        QDomNode item;
        QDomElement iel;

        for(int i = 0; i < items.count(); i++){
            item = items.at(i);
            if(item.isElement()){
                iel = item.toElement();
                if(iel.tagName() == ZLIST_ITEM_NAME){
                    m->appendRow(iel.nodeValue(), iel.toElement().attribute("value",""));
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
    if(i.data().isValid())
	emit activated(i.data());
}
