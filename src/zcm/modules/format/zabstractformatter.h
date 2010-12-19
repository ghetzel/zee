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

#ifndef ZABSTRACTFORMATTER_H
#define ZABSTRACTFORMATTER_H

#include <QObject>
#include <zutil.h>
#include <zui/zuiutils.h>
#include <zformatterinterface.h>

class ZAbstractFormatter : public ZFormatterInterface{
    Q_OBJECT
    Q_PROPERTY(QString method READ method WRITE setMethod)

public:
    ZAbstractFormatter(QObject *parent=0);
    ZAbstractFormatter(QString method, QObject *parent=0);
    ~ZAbstractFormatter(){}
    void setMethod(QString method);
    QString method() const;

public slots:
    virtual QVariant transform(QVariant)=0;
    void setParam(QString key, QVariant val);

signals:
    void ready(QVariant);

protected:
    QVariant arg(QString key, QString fallback=QString());

private:
    QString _method;
    QHash<QString,QVariant> _args;
};

#endif // ZABSTRACTFORMATTER_H
