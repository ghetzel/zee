/******************************************************************************
*    This file is part of Zee.
*
*    Zee is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    Zee is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with Zee.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

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
