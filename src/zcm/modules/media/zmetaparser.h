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

#ifndef ZMETAPARSER_H
#define ZMETAPARSER_H

#include <QString>
#include <QVariant>
#include <QFile>

class ZMetaParser{
public:
    virtual void setFileName(QString location)=0;
    virtual QVariant field(QString name)=0;
    virtual QVariant fieldf(QString format)=0;
    virtual QString type()=0;

protected:
    QString _name;
    QFile _location;
};

#endif // ZMETAPARSER_H
