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

#ifndef ZINT64_H
#define ZINT64_H

#define HIGH32(x)   static_cast<qint32>((x & 0xFFFFFFFF00000000LL) >> 32)
#define LOW32(x)    static_cast<quint32>(x & 0x00000000FFFFFFFFLL)

#include <QtGlobal>

class zint64
{
public:
    zint64();
    zint64(const zint64&);
    zint64(const qint64);
    zint64 &operator =(const zint64&);
    zint64 &operator =(const qint64);
    zint64 &operator +=(const zint64&);
    zint64 &operator +=(const qint64);
    zint64 &operator -=(const zint64&);
    zint64 &operator -=(const qint64);
    zint64 &operator *=(const zint64&);
    zint64 &operator *=(const qint64);
    const zint64 operator+(const zint64&) const;
    const zint64 operator+(const qint64) const;
    const zint64 operator-(const zint64&) const;
    const zint64 operator-(const qint64) const;
    const zint64 operator*(const zint64&) const;
    const zint64 operator*(const qint64) const;
    bool operator==(const zint64&) const;
    bool operator==(const qint64) const;
    bool operator!=(const zint64&) const;
    bool operator!=(const qint64) const;
    qint64 toLongLong() const;
    qint32 high() const;
    quint32 low() const;
    void setValue(const zint64&);
    void setValue(const qint64);

private:
    qint64 _value;
};

#endif // ZINT64_H
