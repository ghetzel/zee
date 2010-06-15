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
