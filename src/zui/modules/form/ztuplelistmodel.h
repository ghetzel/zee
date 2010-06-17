#ifndef ZTUPLELISTMODEL_H
#define ZTUPLELISTMODEL_H

#include <QAbstractListModel>
#include <QIcon>
#include <zutil.h>

class ZTupleListModel : public QAbstractListModel
{
public:
    ZTupleListModel(QObject *parent=0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    void appendRow(QString text, QVariant data);

private:
    struct ZListTuple{
        QIcon decoration;
        QString display;
        QVariant data;
    };

    QList<ZListTuple> _items;
};

#endif // ZTUPLELISTMODEL_H
