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

#ifndef ZDBUSABSTRACTADAPTOR_H
#define ZDBUSABSTRACTADAPTOR_H

#define ZDBUS_SVCNM   "net.gammazeta.zee"
#define ZDBUS_OPATH   "/"

#include <QDBusAbstractAdaptor>
#include <QDBusConnection>
#include <zee.h>
#include <zutil.h>

class ZDBusAbstractAdaptor : public QDBusAbstractAdaptor
{
public:
    ZDBusAbstractAdaptor(QObject *parent);
    ZDBusAbstractAdaptor(QString name, QObject *parent);
    void setInstance(QObject *instance);
    void registerService();

protected:
    void init();
    virtual QObject *instance(){ return _instance; };

private:
    QString _name;
    QObject *_instance;
};

#endif // ZDBUSABSTRACTADAPTOR_H
