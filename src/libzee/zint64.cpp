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

#include "zint64.h"

zint64::zint64(){
    _value = 0;
}

zint64::zint64(const zint64 &val){
    if(this != &val)
	setValue(val);
}

zint64::zint64(const qint64 val){
    setValue(val);
}

zint64 &zint64::operator =(const zint64 &val){
    if(this != &val)
	setValue(val);
    return *this;
}

zint64 &zint64::operator =(const qint64 val){
    setValue(val);
    return *this;
}

zint64 &zint64::operator +=(const zint64 &val){
    setValue(_value+val._value);
    return *this;
}

zint64 &zint64::operator +=(const qint64 val){
    setValue(_value+val);
    return *this;
}

zint64 &zint64::operator -=(const zint64 &val){
    setValue(_value-val._value);
    return *this;
}

zint64 &zint64::operator -=(const qint64 val){
    setValue(_value-val);
    return *this;
}

zint64 &zint64::operator *=(const zint64 &val){
    setValue(_value*val._value);
    return *this;
}

zint64 &zint64::operator *=(const qint64 val){
    setValue(_value*val);
    return *this;
}


const zint64 zint64::operator+(const zint64 &val) const{
    zint64 rv = *this;
    rv += val;
    return rv;
}

const zint64 zint64::operator+(const qint64 val) const{
    zint64 rv = *this;
    rv += val;
    return rv;
}

const zint64 zint64::operator-(const zint64 &val) const{
    zint64 rv = *this;
    rv -= val;
    return rv;
}

const zint64 zint64::operator-(const qint64 val) const{
    zint64 rv = *this;
    rv -= val;
    return rv;
}

const zint64 zint64::operator*(const zint64 &val) const{
    zint64 rv = *this;
    rv *= val;
    return rv;
}

const zint64 zint64::operator*(const qint64 val) const{
    zint64 rv = *this;
    rv *= val;
    return rv;
}

bool zint64::operator ==(const zint64 &val) const{
    return (_value == val._value);
}

bool zint64::operator ==(const qint64 val) const{
    return (_value == val);
}

bool zint64::operator !=(const zint64 &val) const{
    return !(*this == val);
}

bool zint64::operator !=(const qint64 val) const{
    return !(*this == val);
}

qint32 zint64::high() const{
    if(_value > 0xFFFFFFFF)
	return LOW32(_value)+HIGH32(_value);
    return HIGH32(_value);
}

quint32 zint64::low() const{
    if(_value > 0xFFFFFFFF)
	return 0xFFFFFFFF;
    return LOW32(_value);
}

void zint64::setValue(const zint64 &val){
    setValue(val._value);
}

void zint64::setValue(const qint64 val){
    _value = val;
}

qint64 zint64::toLongLong() const{
    return _value;
}
