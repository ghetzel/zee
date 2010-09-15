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
    return QVariant(in.toString().left(len));
}

QVariant ZStringFormatter::_right(QVariant in, uint len){
    return QVariant(in.toString().right(len));
}

QVariant ZStringFormatter::_leftOf(QVariant in, QString delimiter){
    return QVariant(in.toString().section(delimiter,0,1));
}

QVariant ZStringFormatter::_rightOf(QVariant in, QString delimiter){
    return QVariant(in.toString().section(delimiter,1,1));
}

QVariant ZStringFormatter::_ltrim(QVariant in, QString){
    return in;
}

QVariant ZStringFormatter::_rtrim(QVariant in, QString){
    return in;
}

QVariant ZStringFormatter::_trim(QVariant in, QString charsEx){
    return QVariant(in.toString().remove(QRegExp(charsEx)));
}

QVariant ZStringFormatter::_reverse(QVariant in){
    QString rv;
    QString instr = in.toString();
    for(int i = instr.length(); i >= 0; --i)
        rv += instr[i];
    return QVariant(rv);
}

QVariant ZStringFormatter::_lpad(QVariant in, uint width, QChar pad){
    return QVariant(in.toString().leftJustified(width,pad));
}

QVariant ZStringFormatter::_rpad(QVariant in, uint width, QChar pad){
    return QVariant(in.toString().rightJustified(width,pad));
}

QVariant ZStringFormatter::_upcase(QVariant in){
    return QVariant(in.toString().toUpper());
}

QVariant ZStringFormatter::_downcase(QVariant in){
    return QVariant(in.toString().toLower());
}

QVariant ZStringFormatter::_sentenceCase(QVariant in){
    QString instr = in.toString();
    int index = 0;
    while((index = instr.indexOf(QRegExp("(?:\\.)\\W+(\\w)"),index)) >= 0){
        instr[index] = instr[index].toUpper();
        index += index;
    }

    return QVariant(instr);
}

QVariant ZStringFormatter::_titleCase(QVariant in){
    QString instr = in.toString();
    int index = 0;
    while((index = instr.indexOf(QRegExp("\\b+(\\W)"),index)) >= 0){
        instr[index] = instr[index].toUpper();
        index += index;
    }

    return QVariant(instr);
}

QVariant ZStringFormatter::_squeeze(QVariant in, QChar chr){
    if(chr == '\0')
        return QVariant(in.toString().replace(QRegExp("("+QString(chr)+")\\1+"),chr));
    return QVariant(in.toString().replace(QRegExp("(.)\\1+"),"\\1"));
}

QVariant ZStringFormatter::_lelide(QVariant in, int width, QString abbr){
    QString instr = in.toString();
    if(instr.length() > width){
        instr = instr.remove(0,instr.length()-width);
        instr.replace(QRegExp("^(?:\\W+)?\\w+\\W"),abbr);
    }

    return QVariant(instr);
}

QVariant ZStringFormatter::_relide(QVariant in, int width, QString abbr){
    QString instr = in.toString();
    if(instr.length() > width){
        instr = instr.remove(0,instr.length()-width);
        instr.replace(QRegExp("\\W+\\w+(?:\\W+)?$"),abbr);
    }

    return QVariant(instr);
}

QVariant ZStringFormatter::_elide(QVariant in, int width, QString abbr){
    return QVariant(_lelide(in,qCeil(width/2.0),abbr).toString()+_relide(in,qFloor(width/2.0),"").toString());
}

QVariant ZStringFormatter::_lshift(QVariant in, uint num){
    return in.toString().remove(0,num);
}

QVariant ZStringFormatter::_rshift(QVariant in, uint num){
    QString instr = in.toString();
    instr.chop(num);
    return QVariant(instr);
}

QVariant ZStringFormatter::_concat(QVariant in, QVariant other){
    return QVariant(in.toString()+other.toString());
}

QVariant ZStringFormatter::_repeat(QVariant in, uint times){
    return in.toString().repeated(times);
}
