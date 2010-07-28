#ifndef ZXWINDOWLISTITEM_H
#define ZXWINDOWLISTITEM_H

#include <QtCore>
#include <QPainter>
#include <QStyledItemDelegate>
#include <zutil.h>

class ZXWindowListItem : public QStyledItemDelegate
{
  Q_OBJECT

public:
  ZXWindowListItem(QObject *parent = 0);
  void paint(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index) const;
};

#endif // ZXWINDOWLISTITEM_H
