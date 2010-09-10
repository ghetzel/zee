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

#include "zeventobject.h"

ZEventObject::ZEventObject(QObject *object, const char *method)
{
    _object = object;
    if(object && method)
	addMethod(method);
}

QList<ZMethodObject> ZEventObject::methods(QString key){
    if(_methods.isEmpty() || !_methods.contains(key))
	return QList<ZMethodObject>();
    return _methods.values(key);
}

void ZEventObject::setObject(QObject *object){
    if(object){
	_object = object;
	_methods.clear();
    }
}

QObject *ZEventObject::object(){
    return _object;
}

bool ZEventObject::isValid(){
    return (_object && !_methods.isEmpty());
}

void ZEventObject::addMethod(const char *method){
    //z_log_debug("ZEventObject: Add method "+QString(method));
    _methods.insertMulti(ZMethodObject::name(method),
		    ZMethodObject(_object,method));
}

ZEventObject::ZMethodPair ZEventObject::match(QString localAlias,
					      QString remoteAlias,
					      ZEventObject &remoteObject){
// for each method in this object (keyed by localAlias), search remoteObject
// for methods keyed by remoteAlias, and return the pair of method objects that
// match.

    QList<ZMethodObject> local = methods(localAlias);
    QList<ZMethodObject> remote = remoteObject.methods(remoteAlias);
    return ZEventObject::matchMethodsBySignature(local, remote);
}

ZEventObject::ZMethodPair ZEventObject::matchMethodsBySignature(
	QList<ZMethodObject>signal, QList<ZMethodObject>slot, bool ignoreTypes)
{
    ZMethodObject rv1, rv2;
    foreach(ZMethodObject l, signal){
	foreach(ZMethodObject r, slot){
	//  first check for 1-to-1 type compatibility of a given method pair;
	//  failing that, and if we may ignore type compatibility, just try to
	//  find any two methods with the same number of arguments.
	//  this may be a somewhat unsophisticated fallback, but it works...
	    if(l.args() == r.args() ||
	       ( ignoreTypes && (l.args().count() == r.args().count()) ))
	    {
		rv1 = l;
		rv2 = r;
	    }
	}
    }

    return qMakePair(rv1,rv2);
}
