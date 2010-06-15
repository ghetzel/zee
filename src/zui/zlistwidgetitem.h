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
