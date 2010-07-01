#ifndef ZSQLQUERY_H
#define ZSQLQUERY_H

#define ZCM_SQLQUERY    "zee:sql"

#include <QObject>
#include <QString>
#include <QtSql>
#include <zutil.h>
#include <zconfigurable.h>
#include <zeventmanager.h>

class ZSQLQuery : public QSqlQueryModel, public ZConfigurable
{
    Q_OBJECT

public:
    ZSQLQuery(const ZConfig &el, QObject *parent=0);
    ~ZSQLQuery();

public slots:
    void execute();
    void setQuery(QString);

signals:
    void queryChanged(QString);

private:
    void parse(const ZConfig &el);

private:
    QSqlDatabase _conn;
};

#endif // ZSQLQUERY_H
