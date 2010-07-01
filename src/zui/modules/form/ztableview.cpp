#include "ztableview.h"

ZTableView::ZTableView(const ZConfig &el, QWidget *parent)
    : QTableView(parent),
      ZWidget(el,this)
{
    parse(_config);
}

void ZTableView::parse(const ZConfig &el){
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
