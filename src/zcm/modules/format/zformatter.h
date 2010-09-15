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

#ifndef ZFORMATTER_H
#define ZFORMATTER_H

#define ZCM_FORMATTER       "zee:formatter"

#include <QObject>
#include <zutil.h>
#include <zconfigurable.h>
#include <zeventmanager.h>

#include <zabstractformatter.h>
#include <zstringformatter.h>
#include <zdateformatter.h>

class ZFormatter : public QObject, public ZConfigurable
{
    Q_OBJECT
    Q_PROPERTY(QString type READ type())

public:
    ZFormatter(const ZConfig &el, QObject *parent=0);
    QString type();

public slots:
    void transform(QVariant);

signals:
    void ready(QVariant);

private:
    void parse(const ZConfig &el);
    ZAbstractFormatter *formatter(QString name);

private:
    ZAbstractFormatter *_formatter;
};

#endif // ZFORMATTER_H
