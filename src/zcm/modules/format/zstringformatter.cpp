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


void ZStringFormatter::transform(QVariant val){
    if(method() == ZFMT_METHOD_STR_CONCAT){ //!                      concat
	emit ready(_concat(val,arg(0)));

    }else if(method() == ZFMT_METHOD_STR_DOWNCASE){ //!              downcase
	emit ready(_downcase(val));

    }else if(method() == ZFMT_METHOD_STR_ELIDE){ //!                 elide
	if(arg(1).isValid())
	    emit ready(_elide(val, arg(0).toInt(), arg(1).toString()));
	else
	    emit ready(_elide(val, arg(0).toInt()));

    }else if(method() == ZFMT_METHOD_STR_LEFT){ //!                  left
	emit ready(_left(val,arg(0).toUInt()));

    }else if(method() == ZFMT_METHOD_STR_LEFTOF){ //!                leftOf
	emit ready(_leftOf(val,arg(0).toString()));

    }else if(method() == ZFMT_METHOD_STR_LELIDE){ //!                lelide
	if(arg(1).isValid())
	    emit ready(_lelide(val, arg(0).toInt(), arg(1).toString()));
	else
	    emit ready(_lelide(val, arg(0).toInt()));

    }else if(method() == ZFMT_METHOD_STR_LPAD){ //!                  lpad
	if(arg(1).isValid())
	    emit ready(_lpad(val, arg(0).toUInt(), arg(1).toChar()));
	else
	    emit ready(_lpad(val, arg(0).toUInt()));

    }else if(method() == ZFMT_METHOD_STR_LSHIFT){ //!                lshift
	emit ready(_lshift(val,arg(0).toUInt()));

    }else if(method() == ZFMT_METHOD_STR_LTRIM){ //!                 ltrim
	if(arg(0).isValid())
	    emit ready(_ltrim(val, arg(0).toString()));
	else
	    emit ready(_ltrim(val));

    }else if(method() == ZFMT_METHOD_STR_RELIDE){ //!                relide
	if(arg(1).isValid())
	    emit ready(_relide(val, arg(0).toInt(), arg(1).toString()));
	else
	    emit ready(_relide(val, arg(0).toInt()));

    }else if(method() == ZFMT_METHOD_STR_REPEAT){ //!                repeat
	emit ready(_repeat(val, arg(0).toUInt()));

    }else if(method() == ZFMT_METHOD_STR_REVERSE){ //!               reverse
	emit ready(_reverse(val));

    }else if(method() == ZFMT_METHOD_STR_RIGHT){ //!                 right
	emit ready(_right(val, arg(0).toUInt()));

    }else if(method() == ZFMT_METHOD_STR_RIGHTOF){ //!               rightOf
	emit ready(_rightOf(val, arg(0).toString()));

    }else if(method() == ZFMT_METHOD_STR_RPAD){ //!                  rpad
	if(arg(1).isValid())
	    emit ready(_rpad(val, arg(0).toUInt(), arg(1).toChar()));
	else
	    emit ready(_rpad(val, arg(0).toUInt()));

    }else if(method() == ZFMT_METHOD_STR_RSHIFT){ //!                rshift
	emit ready(_rshift(val,arg(0).toUInt()));

    }else if(method() == ZFMT_METHOD_STR_RTRIM){ //!                 rtrim
	if(arg(0).isValid())
	    emit ready(_rtrim(val, arg(0).toString()));
	else
	    emit ready(_rtrim(val));

    }else if(method() == ZFMT_METHOD_STR_SCASE){ //!                 capitalize
	emit ready(_sentenceCase(val));

    }else if(method() == ZFMT_METHOD_STR_SQUEEZE){ //!               squeeze
	if(arg(0).isValid())
	    emit ready(_squeeze(val, arg(0).toChar()));
	else
	    emit ready(_squeeze(val));

    }else if(method() == ZFMT_METHOD_STR_TCASE){ //!                 titleize
	emit ready(_titleCase(val));

    }else if(method() == ZFMT_METHOD_STR_TRIM){ //!                  trim
	if(arg(0).isValid())
	    emit ready(_trim(val, arg(0).toString()));
	else
	    emit ready(_trim(val));

    }else if(method() == ZFMT_METHOD_STR_UPCASE){ //!                upcase
	emit ready(_upcase(val));

    }else{
	emit ready(val);
    }
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
