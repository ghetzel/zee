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

#ifndef ZSETTING_H
#define ZSETTING_H

#define ZEE_SETTING	"zee:setting"

#include <QObject>
#include <zutil.h>
#include <zconfigurable.h>
#include <zeventmanager.h>

class ZSetting : public QObject, public ZConfigurable
{
    Q_OBJECT
public:
    ZSetting(const ZConfig &el, QObject *parent=0);
    void parse(const ZConfig&);

public slots:
    void setValue(QVariant);

signals:
    void valueChanged(QVariant);
};

#endif // ZSETTING_H
