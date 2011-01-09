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

#include "zeeadaptor.h"

ZeeAdaptor::ZeeAdaptor(Zee *parent)
    : ZDBusAbstractAdaptor(parent)
{
    init();
}

ZeeAdaptor::ZeeAdaptor(QString name, Zee *parent)
    : ZDBusAbstractAdaptor(name, parent){
    init();
}

void ZeeAdaptor::init(){
    registerService();

    connect(instance(), SIGNAL(styleReloaded()),
            this,       SIGNAL(styleReloaded()));
    connect(instance(), SIGNAL(propertyResponse(QVariant)),
            this,       SLOT(_propertyResponse(QVariant)));
}

Zee *ZeeAdaptor::instance(){
    return QCAST(Zee*,ZDBusAbstractAdaptor::instance());
}

void ZeeAdaptor::_propertyResponse(QVariant res){
    emit propertyResponse(res.toString());
}


void ZeeAdaptor::reloadStyle(){
    if(instance()) instance()->reloadStyle();
}

void ZeeAdaptor::log(QString msg){
    if(instance()) instance()->log(msg);
}

void ZeeAdaptor::logWarning(QString msg){
    if(instance()) instance()->logWarning(msg);
}

void ZeeAdaptor::logError(QString msg){
    if(instance()) instance()->logError(msg);
}

void ZeeAdaptor::logCritical(QString msg){
    if(instance()) instance()->logCritical(msg);
}

void ZeeAdaptor::logDebug(QString msg){
    if(instance()) instance()->logDebug(msg);
}

QString ZeeAdaptor::queryProperty(QString zObjPath){
    if(instance())
        return instance()->queryProperty(zObjPath).toString();
    return QString();
}
