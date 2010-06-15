#include "zxwindowlistitem.h"

ZXWindowListItem::ZXWindowListItem(QObject *parent)
  : QStyledItemDelegate(parent){

}
void ZXWindowListItem::paint(QPainter *painter, const QStyleOptionViewItem &option,
                             const QModelIndex &index) const{
  if(true){ // not yet...
    z_log("ZWLIT: CUSTOM painter used");

    painter->save();

    painter->restore();
  }else{
    z_log("ZWLIT: Default painter used");
  }

  QStyledItemDelegate::paint(painter, option, index);
}
