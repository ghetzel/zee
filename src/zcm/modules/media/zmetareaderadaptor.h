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

#ifndef ZMETAREADERADAPTOR_H
#define ZMETAREADERADAPTOR_H

#include <zdbusabstractadaptor.h>
#include <zmetareader.h>


class ZMetareaderAdaptor : public ZDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "net.gammazeta.zee.MetadataReader")

public:
    ZMetareaderAdaptor(ZMetaReader *parent);
    ZMetareaderAdaptor(QString name, ZMetaReader *parent);

public slots:
    void setFileName(QString location);
    void field(QString name);

signals:
    void fileChanged(QString location);
    void dataChanged();
    void data(QVariant);

private:
    void init();
    ZMetaReader *instance();

private:
    ZMetaReader *_instance();

};

#endif // ZMETAREADERADAPTOR_H
