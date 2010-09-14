#ifndef ZINT64_H
#define ZINT64_H

#include <QtGlobal>

class zint64
{
public:
    zint64();
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
    qint32 high() const;
    qint32 low() const;

private:
    void setValue(const zint64&);
    void setValue(const qint64);

private:
    qint64 _value;
    qint32 _low;
    qint32 _high;
};

#endif // ZINT64_H
