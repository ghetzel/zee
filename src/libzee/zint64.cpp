#include "zint64.h"

zint64::zint64(){
    _value = 0;
    _high = 0;
    _low  = 0;
}

zint64 &zint64::operator =(const zint64 &val){
//  self-assignment check
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



void zint64::setValue(const zint64 &val){
    setValue(val._value);
}

void zint64::setValue(const qint64 val){
    _value = val;
    _high = ((val & 0xFFFFFFFF00000000) >> 32);
    _low =   (val & 0x00000000FFFFFFFF);
}
