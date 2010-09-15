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

#include "zdateformatter.h"

ZDateFormatter::ZDateFormatter(QObject *parent)
    : ZAbstractFormatter(parent){}

void ZDateFormatter::transform(QVariant val){
    if(method() == ZFMT_METHOD_DATE_FORMAT){
        emit ready(_format(val, arg(0).toString(), arg(1).toString()));
    }else{
        emit ready(val);
    }
}


/*! \brief formats an input date (optionally according to \a input-format) as
           \a output-format */
QVariant ZDateFormatter::_format(QVariant in, QString dateFormat,
                                 QString inputFormat){
    QDateTime input;

    if(inputFormat.isEmpty())
        return QVariant(in.toString()).toDateTime().toString(dateFormat);
    else
    //! format option: unix time (seconds)
        if(inputFormat == ZFMT_DATE_FORMAT_IN_UXSEC){
            input = input.fromTime_t(in.toUInt());
            return input.toString(dateFormat);

    //! format option: unix time (milliseconds)
        }else if(inputFormat == ZFMT_DATE_FORMAT_IN_UXMSEC){
            input = input.fromTime_t(in.toUInt()/1000);
            input = input.addMSecs(in.toUInt() % 1000);
            return input.toString(dateFormat);

    //! format option: autodetect
        }else{
            return QDateTime::fromString(in.toString(), inputFormat).toString(dateFormat);
        }

    return in;
}
