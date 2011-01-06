#include "zstring.h"

ZString::ZString() : QString(){}


ZString::ZString(const ZString &other)
    : QString(other){
}

ZString::ZString(const QString &other)
    : QString(other){
}

ZString::ZString(const char *other)
    : QString(other){
}

QString ZString::toQString(){
    return *this;
}

void ZString::_setText(const ZString &other){
    clear();
    prepend(other);
}

void ZString::_setText(const QString &other){
    clear();
    prepend(other);
}

void ZString::_setText(const char *other){
    clear();
    prepend(other);
}

ZString& ZString::operator=(const ZString &other){
    _setText(other);
    return *this;
}

ZString& ZString::operator=(const QString &other){
    _setText(other);
    return *this;
}

ZString& ZString::operator=(const char *other){
    _setText(other);
    return *this;
}


// STATIC METHODS
ZString ZString::left(QVariant in, uint len){
    return in.toString().left(len);
}

ZString ZString::right(QVariant in, uint len){
    return in.toString().right(len);
}

ZString ZString::leftOf(QVariant in, QString delimiter){
    ZString instr = in.toString();
    if(instr.contains(delimiter))
        return instr.substring(0, instr.indexOf(delimiter));
    return instr;
}

ZString ZString::leftOfLast(QVariant in, QString delimiter){
    ZString instr = in.toString();
    if(instr.contains(delimiter))
        return instr.substring(0, instr.lastIndexOf(delimiter));
    return instr;
}

ZString ZString::rightOf(QVariant in, QString delimiter){
    ZString instr = in.toString();
    if(instr.contains(delimiter))
        return instr.substring(instr.indexOf(delimiter)+delimiter.length(),
                               instr.length());
    return instr;
}

ZString ZString::rightOfLast(QVariant in, QString delimiter){
    ZString instr = in.toString();
    if(instr.contains(delimiter))
        return instr.substring(instr.lastIndexOf(delimiter)+delimiter.length(),
                               instr.length());
    return instr;
}


//stub
ZString ZString::ltrim(QVariant in, QString charsEx){
    return ZString(in.toString());
}

//stub
ZString ZString::rtrim(QVariant in, QString charsEx){
    return ZString(in.toString());
}

//stub
ZString ZString::trim(QVariant in, QString charsEx){
    return ZString(in.toString());
}

ZString ZString::reverse(QVariant in){
    QString rv;
    QString instr = in.toString();
    for(int i = instr.length(); i >= 0; --i)
        rv += instr[i];
    return rv;
}

ZString ZString::lpad(QVariant in, uint width, QChar pad){
    return in.toString().leftJustified(width,pad);
}

ZString ZString::rpad(QVariant in, uint width, QChar pad){
    return in.toString().rightJustified(width,pad);
}

ZString ZString::upcase(QVariant in){
    return in.toString().toUpper();
}

ZString ZString::downcase(QVariant in){
    return in.toString().toLower();
}

ZString ZString::sentenceCase(QVariant in){
    QString instr = in.toString();
    int index = 0;
    while((index = instr.indexOf(QRegExp("(?:\\.)\\W+(\\w)"),index)) >= 0){
        instr[index] = instr[index].toUpper();
        index += index;
    }

    return instr;
}

ZString ZString::titleCase(QVariant in){
    QString instr = in.toString();
    int index = 0;
    while((index = instr.indexOf(QRegExp("\\b+(\\W)"),index)) >= 0){
        instr[index] = instr[index].toUpper();
        index += index;
    }

    return instr;
}

ZString ZString::squeeze(QVariant in, QChar chr){
//    if(chr == '\0')
//        return in.toString().replace(QRegExp("[.]+"),"\\1");
    return in.toString().replace(QRegExp("["+QString(chr)+"]{2,}"),chr);
}

ZString ZString::lelide(QVariant in, int width, QString abbr){
    QString instr = in.toString();
    if(instr.length() > width){
        instr = instr.remove(0,instr.length()-width);
        instr.replace(QRegExp("^(?:\\W+)?\\w+\\W"),abbr);
    }

    return instr;
}

ZString ZString::relide(QVariant in, int width, QString abbr){
    QString instr = in.toString();
    if(instr.length() > width){
        instr = instr.remove(0,instr.length()-width);
        instr.replace(QRegExp("\\W+\\w+(?:\\W+)?$"),abbr);
    }

    return instr;
}

ZString ZString::elide(QVariant in, int width, QString abbr){
    return ZString::lelide(in,qCeil(width/2.0),abbr)+
           ZString::relide(in,qFloor(width/2.0),"");
}

ZString ZString::lshift(QVariant in, uint num){
    return in.toString().remove(0,num);
}

ZString ZString::rshift(QVariant in, uint num){
    QString instr = in.toString();
    instr.chop(num);
    return instr;
}

ZString ZString::concat(QVariant in, QVariant other){
    return in.toString()+other.toString();
}

ZString ZString::repeat(QVariant in, uint times){
    return in.toString().repeated(times);
}

ZString ZString::substring(QVariant in, int beginIndex, int length){
    if(length == 0)
        return ZString();

    QString instr = in.toString();
    QString rv;

    for(int i = 0; i < instr.length(); i++){
        if(length > 0){
            if(i >= beginIndex && i < (beginIndex+length)){
                rv += instr.at(i);
            }
        }else{
            if(i >= (beginIndex+length+1) && i < (beginIndex+1)){
                rv += instr.at(i);
            }
        }
    }

    return rv;
}

ZString ZString::find(QVariant in, QString subject){
    ZString instr = in.toString();
    QRegExp rx(subject);
    int i = 0;
    if((i = rx.indexIn(instr)) != -1){
        if(rx.exactMatch(subject))
            return instr.substring(i,rx.matchedLength());
    }

    return ZString();
}

ZString ZString::match(QVariant in, QRegExp pattern){
    ZString instr = in.toString();
    int i = 0;
    if((i = pattern.indexIn(instr)) != -1){
        return instr.substring(i,pattern.matchedLength());
    }

    return ZString();
}

// INSTANCE METHODS
ZString ZString::left(uint len){
    return ZString::left(toQString(), len);
}

ZString ZString::right(uint len){
    return ZString::right(toQString(), len);
}

ZString ZString::leftOf(QString delimiter){
    return ZString::leftOf(toQString(), delimiter);
}

ZString ZString::leftOfLast(QString delimiter){
    return ZString::leftOfLast(toQString(), delimiter);
}

ZString ZString::rightOf(QString delimiter){
    return ZString::rightOf(toQString(), delimiter);
}

ZString ZString::rightOfLast(QString delimiter){
    return ZString::rightOfLast(toQString(), delimiter);
}

ZString ZString::ltrim(QString charsEx){
    return ZString::ltrim(toQString(), charsEx);
}

ZString ZString::rtrim(QString charsEx){
    return ZString::rtrim(toQString(), charsEx);
}

ZString ZString::trim(QString charsEx){
    return ZString::trim(toQString(), charsEx);
}

ZString ZString::reverse(){
    return ZString::reverse(toQString());
}

ZString ZString::lpad(uint width, QChar pad){
    return ZString::lpad(toQString(), width, pad);
}

ZString ZString::rpad(uint width, QChar pad){
    return ZString::rpad(toQString(), width, pad);
}

ZString ZString::upcase(){
    return ZString::upcase(toQString());
}

ZString ZString::downcase(){
    return ZString::downcase(toQString());
}

ZString ZString::sentenceCase(){
    return ZString::sentenceCase(toQString());
}

ZString ZString::titleCase(){
    return ZString::titleCase(toQString());
}

ZString ZString::squeeze(QChar chr){
    return ZString::squeeze(toQString(), chr);
}

ZString ZString::lelide(int width, QString abbr){
    return ZString::lelide(toQString(), width, abbr);
}

ZString ZString::relide(int width, QString abbr){
    return ZString::relide(toQString(), width, abbr);
}

ZString ZString::elide(int width, QString abbr){
    return ZString::elide(toQString(), width, abbr);
}

ZString ZString::lshift(uint num){
    return ZString::lshift(toQString(), num);
}

ZString ZString::rshift(uint num){
    return ZString::rshift(toQString(), num);
}

ZString ZString::concat(const QVariant &other){
    return ZString::concat(toQString(), other);
}

ZString ZString::repeat(uint times){
    return ZString::repeat(toQString(), times);
}

ZString ZString::substring(int beginIndex, int length){
    return ZString::substring(toQString(), beginIndex, length);
}


ZString ZString::find(QString subject){
    return ZString::find(toQString(), subject);
}

ZString ZString::match(QRegExp pattern){
    return ZString::match(toQString(), pattern);
}
