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

#include "zmethodobject.h"

ZMethodObject::ZMethodObject(){
    _object = NULL;
    _method = NULL;
}

ZMethodObject::ZMethodObject(QObject *object, const char *method)
{
    _object = object;
    _method = method;
}

bool ZMethodObject::isValid(){
    return (_object && _method);
}

QObject *ZMethodObject::object(){
    return _object;
}

const char *ZMethodObject::method(){
    return _method;
}

void ZMethodObject::setObject(QObject *object){
    _object = object;
}

void ZMethodObject::setMethod(const char *method){
    _method = method;
}

QString ZMethodObject::name(const char *method){
    return DETYPESIG(METHODNAME(method));
}

QStringList ZMethodObject::args(const char *method){
    return METHODARGS(method).split(",");
}

QString ZMethodObject::signature(const char *method){
    return ZMethodObject::name(method)+"("+
	   ZMethodObject::args(method).join(",")+")";
}

QList<QVariant::Type> ZMethodObject::argTypes(const char *method){
    QList<QVariant::Type> rv;
    foreach(QString arg, ZMethodObject::args(method))
	rv << QVariant::nameToType(arg.toAscii().data());
    return rv;
}

QString ZMethodObject::name(){
    if(!isValid())
	return QString();
    return ZMethodObject::name(_method);
}

QStringList ZMethodObject::args(){
    if(!isValid())
	return QStringList();
    return ZMethodObject::args(_method);
}

QString ZMethodObject::signature(){
    if(!isValid())
	return QString();
    return ZMethodObject::signature(_method);
}

QList<QVariant::Type> ZMethodObject::argTypes(){
    if(!isValid())
	return QList<QVariant::Type>();
    return ZMethodObject::argTypes(_method);
}
