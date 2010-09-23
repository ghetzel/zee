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

#ifndef ZDATEFORMATTER_H
#define ZDATEFORMATTER_H

#define ZCM_FORMATTER_DATE          "date"

#define ZFMT_METHOD_DATE_FORMAT     "format"

#define ZFMT_DATE_FORMAT_IN_UXSEC   "U"
#define ZFMT_DATE_FORMAT_IN_UXMSEC  "u"

#include <zabstractformatter.h>
#include <libzee/zdatetime.h>

class ZDateFormatter : public ZAbstractFormatter
{
    Q_OBJECT
public:
    ZDateFormatter(QObject *parent=0);

public slots:
    virtual void transform(QVariant);
    
private:
    QVariant _format(QVariant in, QString dateFormat,
                     QString inputFormat=QString());
};

#endif // ZDATEFORMATTER_H
