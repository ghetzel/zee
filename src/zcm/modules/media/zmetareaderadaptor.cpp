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

#include "zmetareaderadaptor.h"

ZMetareaderAdaptor::ZMetareaderAdaptor(ZMetaReader *parent)
    : ZDBusAbstractAdaptor(parent)
{
    init();
}

ZMetareaderAdaptor::ZMetareaderAdaptor(QString name, ZMetaReader *parent)
    : ZDBusAbstractAdaptor(name, parent){
    init();
}


void ZMetareaderAdaptor::init(){
    if(instance()){
        connect(instance(), SIGNAL(fileChanged(QString)),
                this,       SIGNAL(fileChanged(QString)));
        connect(instance(), SIGNAL(dataChanged()),
                this,       SIGNAL(dataChanged()));
        connect(instance(), SIGNAL(data(QVariant)),
                this,       SIGNAL(data(QVariant)));

        registerService();
    }
}

ZMetaReader *ZMetareaderAdaptor::instance(){
    return QCAST(ZMetaReader*,ZDBusAbstractAdaptor::instance());
}

void ZMetareaderAdaptor::setFileName(QString location){
    if(instance())
        instance()->setFileName(location);
}

void ZMetareaderAdaptor::field(QString name){
    if(instance())
        instance()->field(name);
}
