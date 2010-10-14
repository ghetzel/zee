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

#ifndef ZSTRINGFORMATTER_H
#define ZSTRINGFORMATTER_H

#define ZCM_FORMATTER_STRING        "string"

#define ZFMT_METHOD_STR_LEFT        "left"
#define ZFMT_METHOD_STR_RIGHT       "right"
#define ZFMT_METHOD_STR_LEFTOF      "leftOf"
#define ZFMT_METHOD_STR_RIGHTOF     "rightOf"
#define ZFMT_METHOD_STR_LTRIM       "ltrim"
#define ZFMT_METHOD_STR_RTRIM       "rtrim"
#define ZFMT_METHOD_STR_TRIM        "trim"
#define ZFMT_METHOD_STR_REVERSE     "reverse"
#define ZFMT_METHOD_STR_LPAD        "lpad"
#define ZFMT_METHOD_STR_RPAD        "rpad"
#define ZFMT_METHOD_STR_UPCASE      "upcase"
#define ZFMT_METHOD_STR_DOWNCASE    "downcase"
#define ZFMT_METHOD_STR_SCASE       "capitalize"
#define ZFMT_METHOD_STR_TCASE       "titleize"
#define ZFMT_METHOD_STR_SQUEEZE     "squeeze"
#define ZFMT_METHOD_STR_LELIDE      "lelide"
#define ZFMT_METHOD_STR_RELIDE      "relide"
#define ZFMT_METHOD_STR_ELIDE       "elide"
#define ZFMT_METHOD_STR_LSHIFT      "lshift"
#define ZFMT_METHOD_STR_RSHIFT      "rshift"
#define ZFMT_METHOD_STR_CONCAT      "concat"
#define ZFMT_METHOD_STR_REPEAT      "repeat"
#define ZFMT_METHOD_STR_SUBSTR      "substring"

#include <libzee/zstring.h>
#include <zabstractformatter.h>

class ZStringFormatter : public ZAbstractFormatter
{
    Q_OBJECT
public:
    ZStringFormatter(QObject *parent=0);

public slots:
    virtual QVariant transform(QVariant);

private:
    QVariant _left(QVariant in, uint len);
    QVariant _right(QVariant in, uint len);
    QVariant _leftOf(QVariant in, QString delimiter);
    QVariant _rightOf(QVariant in, QString delimiter);
    QVariant _ltrim(QVariant in, QString charsEx="\\w+");
    QVariant _rtrim(QVariant in, QString charsEx="\\w+");
    QVariant _trim(QVariant in, QString charsEx="\\w+");
    QVariant _reverse(QVariant in);
    QVariant _lpad(QVariant in, uint width, QChar pad=' ');
    QVariant _rpad(QVariant in, uint width, QChar pad=' ');
    QVariant _upcase(QVariant in);
    QVariant _downcase(QVariant in);
    QVariant _sentenceCase(QVariant in);
    QVariant _titleCase(QVariant in);
    QVariant _squeeze(QVariant in, QChar chr='\0');
    QVariant _lelide(QVariant in, int width, QString abbr="...");
    QVariant _relide(QVariant in, int width, QString abbr="...");
    QVariant _elide(QVariant in, int width, QString abbr="...");
    QVariant _lshift(QVariant in, uint num);
    QVariant _rshift(QVariant in, uint num);
    QVariant _concat(QVariant in, QVariant other);
    QVariant _repeat(QVariant in, uint times);
};

#endif // ZSTRINGFORMATTER_H
