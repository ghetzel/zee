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

#ifndef ZEEADAPTOR_H
#define ZEEADAPTOR_H

#include <zdbusabstractadaptor.h>
#include <zee.h>

class ZeeAdaptor : public ZDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "net.gammazeta.zee.Zee")

public:
    ZeeAdaptor(Zee *parent);
    ZeeAdaptor(QString name, Zee *parent);

public slots:
    void reloadStyleSheet();
    void log(QString);
    void logWarning(QString);
    void logError(QString);
    void logCritical(QString);
    void logDebug(QString);

signals:
    void styleReloaded();

private:
    void init();
    Zee *instance();
};

#endif // ZEEADAPTOR_H
