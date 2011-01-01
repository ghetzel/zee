#ifndef ZDATAMODEL_H
#define ZDATAMODEL_H


#define ZCM_DATAMODEL        "zee:datamodel"

#include <QObject>
#include <QVariant>
#include <QtSql/QSqlRelationalTableModel>
#include <zutil.h>
#include <zconfigurable.h>
#include <zeventmanager.h>


class ZDataModel : public QSqlRelationalTableModel, public ZConfigurable
{
public:
    ZDataModel(const ZConfig &el, QObject *parent=0, QSqlDatabase db = QSqlDatabase());
    void parse(const ZConfig &el);

private:
    QHash<QString,int> _columns;
};

#endif // ZDATAMODEL_H
