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

#ifndef ZTRANSFORMATION_H
#define ZTRANSFORMATION_H

#define ZCM_TRANSFORMATION          "zee:transform"

#include <QObject>
#include <zconfigurable.h>
#include <zeventmanager.h>
#include <zformatter.h>

class ZTransformation : public QObject, public ZConfigurable
{
    Q_OBJECT
public:
    ZTransformation(const ZConfig &el, QObject *parent=0);

public slots:
    void transform(QVariant);

signals:
    void start(QVariant);
    void ready(QVariant);

private:
    void parse(const ZConfig &el);
    void chainFormatters();

private:
    QList<ZFormatter*> _formatters;
};

#endif // ZTRANSFORMATION_H
