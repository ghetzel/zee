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

#ifndef ZMETHODOBJECT_H
#define ZMETHODOBJECT_H

#include <QObject>
#include <QStringList>
#include <zutil.h>

class ZMethodObject
{
public:
    ZMethodObject();
    ZMethodObject(QObject *object, const char *method);
    QObject *object();
    void setObject(QObject *object);
    void setMethod(const char *method);
    const char *method();
    QString name();
    QStringList args();
    QString signature();
    QList<QVariant::Type> argTypes();
    bool isValid();

public:
    static QString name(const char *method);
    static QStringList args(const char *method);
    static QString signature(const char *method);
    static QList<QVariant::Type> argTypes(const char *method);
private:
    QObject *_object;
    const char *_method;
    QString _name;
    QString _signature;
    bool _null;
};

#endif // ZMETHODOBJECT_H
