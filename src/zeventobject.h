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

#ifndef ZEVENTOBJECT_H
#define ZEVENTOBJECT_H

#include <QtCore>
#include <zutil.h>
#include <zmethodobject.h>

class ZEventObject
{
public:
    typedef QPair<ZMethodObject,ZMethodObject> ZMethodPair;
    ZEventObject(QObject *object=0, const char *method=0);
    QList<ZMethodObject> methods(QString key);
    void setObject(QObject *object);
    QObject *object();
    void addMethod(const char *method);
    bool isValid();
    ZMethodPair match(QString localAlias,
		      QString remoteAlias,
		      ZEventObject &remoteObject);
    static QStringList getSurrogateArgs(QString surrogates);
    static ZMethodPair matchMethodsBySignature(QList<ZMethodObject> signal,
					       QList<ZMethodObject> slot,
					       bool ignoreTypes=false,
					       QString surrogates=QString());

private:
    QObject *_object;
    QHash<QString, ZMethodObject> _methods;
private:
    void init();
};

#endif // ZEVENTOBJECT_H
