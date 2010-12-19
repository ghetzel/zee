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

#include "zstringformatter.h"

ZStringFormatter::ZStringFormatter(QObject *parent)
    : ZAbstractFormatter(parent){}


QVariant ZStringFormatter::transform(QVariant val){
    if(method() == ZFMT_METHOD_STR_CONCAT){ //!                      concat( with )
        return _concat(val,arg("with",ZML_DEFAULT_PARAM_NAME));

    }else if(method() == ZFMT_METHOD_STR_DOWNCASE){ //!              downcase
        return _downcase(val);

    }else if(method() == ZFMT_METHOD_STR_ELIDE){ //!                 elide( [maxLength [, placeholder]] )
        if(arg("placeholder").isValid())
            return _elide(val, arg("maxLength",ZML_DEFAULT_PARAM_NAME).toInt(), arg("placeholder").toString());
        else
            return _elide(val, arg("maxLength",ZML_DEFAULT_PARAM_NAME).toInt());

    }else if(method() == ZFMT_METHOD_STR_LEFT){ //!                  left( length )
        return _left(val, arg("length",ZML_DEFAULT_PARAM_NAME).toUInt());

    }else if(method() == ZFMT_METHOD_STR_LEFTOF){ //!                leftOf( delimiter )
        return _leftOf(val, arg("delimiter",ZML_DEFAULT_PARAM_NAME).toString());

    }else if(method() == ZFMT_METHOD_STR_LELIDE){ //!                lelide( [maxLength [, placeholder]] )
        if(arg("placeholder").isValid())
            return _lelide(val, arg("maxLength",ZML_DEFAULT_PARAM_NAME).toInt(), arg("placeholder").toString());
        else
            return _lelide(val, arg("maxLength",ZML_DEFAULT_PARAM_NAME).toInt());

    }else if(method() == ZFMT_METHOD_STR_LPAD){ //!                  lpad( length [, symbol] )
        if(arg("symbol").isValid())
            return _lpad(val, arg("length",ZML_DEFAULT_PARAM_NAME).toUInt(), arg("symbol").toChar());
        else
            return _lpad(val, arg("length",ZML_DEFAULT_PARAM_NAME).toUInt());

    }else if(method() == ZFMT_METHOD_STR_LSHIFT){ //!                lshift( places )
        return _lshift(val, arg("places", ZML_DEFAULT_PARAM_NAME).toUInt());

    }else if(method() == ZFMT_METHOD_STR_LTRIM){ //!                 ltrim( [pattern] )
        if(arg("pattern").isValid())
            return _ltrim(val, arg("pattern",ZML_DEFAULT_PARAM_NAME).toString());
        else
            return _ltrim(val);

    }else if(method() == ZFMT_METHOD_STR_RELIDE){ //!                relide( [maxLength [, placeholder]] )
        if(arg("placeholder").isValid())
            return _relide(val, arg("maxLength",ZML_DEFAULT_PARAM_NAME).toInt(), arg("placeholder").toString());
        else
            return _relide(val, arg("maxLength",ZML_DEFAULT_PARAM_NAME).toInt());

    }else if(method() == ZFMT_METHOD_STR_REPEAT){ //!                repeat( times )
        return _repeat(val, arg("times",ZML_DEFAULT_PARAM_NAME).toUInt());

    }else if(method() == ZFMT_METHOD_STR_REVERSE){ //!               reverse
        return _reverse(val);

    }else if(method() == ZFMT_METHOD_STR_RIGHT){ //!                 right( length )
        return _right(val, arg("length",ZML_DEFAULT_PARAM_NAME).toUInt());

    }else if(method() == ZFMT_METHOD_STR_RIGHTOF){ //!               rightOf( delimiter )
        return _rightOf(val, arg("delimiter",ZML_DEFAULT_PARAM_NAME).toString());

    }else if(method() == ZFMT_METHOD_STR_RPAD){ //!                  rpad( length [, symbol] )
        if(arg("symbol").isValid())
            return _rpad(val, arg("length",ZML_DEFAULT_PARAM_NAME).toUInt(), arg("symbol").toChar());
        else
            return _rpad(val, arg("length",ZML_DEFAULT_PARAM_NAME).toUInt());

    }else if(method() == ZFMT_METHOD_STR_RSHIFT){ //!                rshift( places )
        return _rshift(val, arg("places",ZML_DEFAULT_PARAM_NAME).toUInt());

    }else if(method() == ZFMT_METHOD_STR_RTRIM){ //!                 rtrim( [pattern] )
        if(arg("pattern").isValid())
            return _rtrim(val, arg("pattern",ZML_DEFAULT_PARAM_NAME).toString());
        else
            return _rtrim(val);

    }else if(method() == ZFMT_METHOD_STR_SCASE){ //!                 capitalize
        return _sentenceCase(val);

    }else if(method() == ZFMT_METHOD_STR_SQUEEZE){ //!               squeeze( [symbol] )
        if(arg("symbol").isValid())
            return _squeeze(val, arg("symbol",ZML_DEFAULT_PARAM_NAME).toChar());
        else
            return _squeeze(val);

    }else if(method() == ZFMT_METHOD_STR_TCASE){ //!                 titleize
        return _titleCase(val);

    }else if(method() == ZFMT_METHOD_STR_TRIM){ //!                  trim( [pattern] )
        if(arg("pattern").isValid())
            return _trim(val, arg("pattern",ZML_DEFAULT_PARAM_NAME).toString());
        else
            return _trim(val);

    }else if(method() == ZFMT_METHOD_STR_UPCASE){ //!                upcase
        return _upcase(val);
    }

    return val;
}

QVariant ZStringFormatter::_left(QVariant in, uint len){
    return QVariant(ZString::left(in,len));
}

QVariant ZStringFormatter::_right(QVariant in, uint len){
    return QVariant(ZString::right(in,len));
}

QVariant ZStringFormatter::_leftOf(QVariant in, QString delimiter){
    return QVariant(ZString::leftOf(in, delimiter));
}

QVariant ZStringFormatter::_rightOf(QVariant in, QString delimiter){
    return QVariant(ZString::rightOf(in, delimiter));
}

QVariant ZStringFormatter::_ltrim(QVariant in, QString){
    return QVariant(ZString::ltrim(in));
}

QVariant ZStringFormatter::_rtrim(QVariant in, QString){
    return QVariant(ZString::rtrim(in));
}

QVariant ZStringFormatter::_trim(QVariant in, QString charsEx){
    return QVariant(ZString::trim(in,charsEx));
}

QVariant ZStringFormatter::_reverse(QVariant in){
    return QVariant(ZString::reverse(in));
}

QVariant ZStringFormatter::_lpad(QVariant in, uint width, QChar pad){
    return QVariant(ZString::lpad(in, width, pad));
}

QVariant ZStringFormatter::_rpad(QVariant in, uint width, QChar pad){
    return QVariant(ZString::rpad(in, width, pad));
}

QVariant ZStringFormatter::_upcase(QVariant in){
    return QVariant(ZString::upcase(in));
}

QVariant ZStringFormatter::_downcase(QVariant in){
    return QVariant(ZString::downcase(in));
}

QVariant ZStringFormatter::_sentenceCase(QVariant in){
    return QVariant(ZString::sentenceCase(in));
}

QVariant ZStringFormatter::_titleCase(QVariant in){
    return QVariant(ZString::titleCase(in));
}

QVariant ZStringFormatter::_squeeze(QVariant in, QChar chr){
    return QVariant(ZString::squeeze(in, chr));
}

QVariant ZStringFormatter::_lelide(QVariant in, int width, QString abbr){
    return QVariant(ZString::lelide(in, width, abbr));
}

QVariant ZStringFormatter::_relide(QVariant in, int width, QString abbr){
    return QVariant(ZString::relide(in, width, abbr));
}

QVariant ZStringFormatter::_elide(QVariant in, int width, QString abbr){
    return QVariant(ZString::elide(in, width, abbr));
}

QVariant ZStringFormatter::_lshift(QVariant in, uint num){
    return QVariant(ZString::lshift(in, num));
}

QVariant ZStringFormatter::_rshift(QVariant in, uint num){
    return QVariant(ZString::rshift(in, num));
}

QVariant ZStringFormatter::_concat(QVariant in, QVariant other){
    return QVariant(ZString::concat(in, other));
}

QVariant ZStringFormatter::_repeat(QVariant in, uint times){
    return QVariant(ZString::repeat(in, times));
}
