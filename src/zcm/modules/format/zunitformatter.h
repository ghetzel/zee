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


#ifndef ZUNITFORMATTER_H
#define ZUNITFORMATTER_H

#define ZCM_FORMATTER_UNIT		"unit"

#define ZUNIT_UT_DBPATH			"/usr/share/udunits/udunits2.xml"

#include <udunits2/udunits.h>
#include <zabstractformatter.h>


class ZUnitFormatter : public ZAbstractFormatter
{
    Q_OBJECT
public:
    ZUnitFormatter(QObject *parent=0);

public slots:
    virtual QVariant transform(QVariant);

private:
    int _utInitCode;
};

#endif // ZUNITFORMATTER_H




//#define ZFMT_METHOD_UNIT_FAHRENHEIT	"F|fahrenheit"
//#define ZFMT_METHOD_UNIT_CELSIUS	"C|celsius"
//#define ZFMT_METHOD_UNIT_KELVIN		"K|kelvin"
//
//// bits
//#define ZFMT_METHOD_UNIT_BITS		"b|bits|bit"
//#define ZFMT_METHOD_UNIT_KILOBITS	"Kb|kilobits|kilobit"
//#define ZFMT_METHOD_UNIT_MEGABITS	"Mb|megabits|megabit"
//#define ZFMT_METHOD_UNIT_GIGABITS	"Gb|gigabits|gigabit"
//#define ZFMT_METHOD_UNIT_TERABITS	"Tb|terabits|terabit"
//#define ZFMT_METHOD_UNIT_PETABITS	"Pb|petabits|petabit"
//#define ZFMT_METHOD_UNIT_EXABITS	"Eb|exabits|exabit"
//#define ZFMT_METHOD_UNIT_ZETTABITS	"Zb|zettabits|zettabit"
//#define ZFMT_METHOD_UNIT_YOTTABITS	"Yb|yottabits|yottabit"
//
//// bytes
//#define ZFMT_METHOD_UNIT_BYTES		"B|bytes"
//#define ZFMT_METHOD_UNIT_KILOBYTES	"KB|kilobytes|kilobyte"
//#define ZFMT_METHOD_UNIT_MEGABYTES	"MB|megabytes|megabyte"
//#define ZFMT_METHOD_UNIT_GIGABYTES	"GB|gigabytes|gigabyte"
//#define ZFMT_METHOD_UNIT_TERABYTES	"TB|terabytes|terabyte"
//#define ZFMT_METHOD_UNIT_PETABYTES	"PB|petabytes|petabyte"
//#define ZFMT_METHOD_UNIT_EXABYTES	"EB|exabytes|exabyte"
//#define ZFMT_METHOD_UNIT_ZETTABYTES	"ZB|zettabytes|zettabyte"
//#define ZFMT_METHOD_UNIT_YOTTABYTES	"YB|yottabytes|yottabyte"
//
//// linear distances
////	imperial
//#define ZFMT_METHOD_UNIT_INCHES		"in|inches|inch"
//#define ZFMT_METHOD_UNIT_FEET		"ft|feet|foot"
//#define ZFMT_METHOD_UNIT_YARDS		"yd|yards|yard"
//
//// metric
//#define ZFMT_METHOD_UNIT_YOCTOMETERS	"ym|yoctometers|yoctometer"
//#define ZFMT_METHOD_UNIT_ZEPTOMETERS	"zm|zeptometers|zeptometer"
//#define ZFMT_METHOD_UNIT_ATTOMETERS	"am|attometers|attometer"
//#define ZFMT_METHOD_UNIT_FEMTOMETERS	"fm|femtometers|femtometer"
//#define ZFMT_METHOD_UNIT_PICOMETERS	"pm|picometers|picometer"
//#define ZFMT_METHOD_UNIT_
