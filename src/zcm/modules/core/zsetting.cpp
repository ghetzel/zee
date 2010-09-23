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

#include "zsetting.h"

ZSetting::ZSetting(const ZConfig &el, QObject *parent)
    : QObject(parent),
      ZConfigurable(el,this)
{
    zEvent->registerSignal(this, SIGNAL(valueChanged(QVariant)));
    zEvent->registerSlot(this, SLOT(setValue(QVariant)));
}

void ZSetting::parse(const ZConfig&){}

void ZSetting::setValue(QVariant val){
    setProperty("value", val);
    emit valueChanged(val);
}
