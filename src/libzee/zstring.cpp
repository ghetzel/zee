#include "zstring.h"


ZString::ZString(ZString &other)
    : QString(){
    _value = other.toQString();
}

ZString::ZString(QString &other)
    : QString(){
    _value = other;
}

QString ZString::toQString(){
    return _value;
}


// STATIC METHODS
QString ZString::left(QVariant in, uint len){
    return in.toString().left(len);
}

QString ZString::right(QVariant in, uint len){
    return in.toString().right(len);
}

QString ZString::leftOf(QVariant in, QString delimiter){
    QString instr = in.toString();
    if(instr.contains(delimiter))
        return instr.section(delimiter,0,1);
    return in.toString();
}

QString ZString::rightOf(QVariant in, QString delimiter){
    QString instr = in.toString();
    if(instr.contains(delimiter))
        return instr.section(delimiter,1,1);
    return in.toString();
}

QString ZString::ltrim(QVariant in, QString){
    return in.toString();
}

QString ZString::rtrim(QVariant in, QString){
    return in.toString();
}

QString ZString::trim(QVariant in, QString charsEx){
    return in.toString().remove(QRegExp(charsEx));
}

QString ZString::reverse(QVariant in){
    QString rv;
    QString instr = in.toString();
    for(int i = instr.length(); i >= 0; --i)
        rv += instr[i];
    return rv;
}

QString ZString::lpad(QVariant in, uint width, QChar pad){
    return in.toString().leftJustified(width,pad);
}

QString ZString::rpad(QVariant in, uint width, QChar pad){
    return in.toString().rightJustified(width,pad);
}

QString ZString::upcase(QVariant in){
    return in.toString().toUpper();
}

QString ZString::downcase(QVariant in){
    return in.toString().toLower();
}

QString ZString::sentenceCase(QVariant in){
    QString instr = in.toString();
    int index = 0;
    while((index = instr.indexOf(QRegExp("(?:\\.)\\W+(\\w)"),index)) >= 0){
        instr[index] = instr[index].toUpper();
        index += index;
    }

    return instr;
}

QString ZString::titleCase(QVariant in){
    QString instr = in.toString();
    int index = 0;
    while((index = instr.indexOf(QRegExp("\\b+(\\W)"),index)) >= 0){
        instr[index] = instr[index].toUpper();
        index += index;
    }

    return instr;
}

QString ZString::squeeze(QVariant in, QChar chr){
    if(chr == '\0')
        return in.toString().replace(QRegExp("("+QString(chr)+")\\1+"),chr);
    return in.toString().replace(QRegExp("(.)\\1+"),"\\1");
}

QString ZString::lelide(QVariant in, int width, QString abbr){
    QString instr = in.toString();
    if(instr.length() > width){
        instr = instr.remove(0,instr.length()-width);
        instr.replace(QRegExp("^(?:\\W+)?\\w+\\W"),abbr);
    }

    return instr;
}

QString ZString::relide(QVariant in, int width, QString abbr){
    QString instr = in.toString();
    if(instr.length() > width){
        instr = instr.remove(0,instr.length()-width);
        instr.replace(QRegExp("\\W+\\w+(?:\\W+)?$"),abbr);
    }

    return instr;
}

QString ZString::elide(QVariant in, int width, QString abbr){
    return ZString::lelide(in,qCeil(width/2.0),abbr)+
           ZString::relide(in,qFloor(width/2.0),"");
}

QString ZString::lshift(QVariant in, uint num){
    return in.toString().remove(0,num);
}

QString ZString::rshift(QVariant in, uint num){
    QString instr = in.toString();
    instr.chop(num);
    return instr;
}

QString ZString::concat(QVariant in, QVariant other){
    return in.toString()+other.toString();
}

QString ZString::repeat(QVariant in, uint times){
    return in.toString().repeated(times);
}


// INSTANCE METHODS
QString ZString::left(uint len){
    return ZString::left(_value, len);
}

QString ZString::right(uint len){
    return ZString::right(_value, len);
}

QString ZString::leftOf(QString delimiter){
    return ZString::leftOf(_value, delimiter);
}

QString ZString::rightOf(QString delimiter){
    return ZString::rightOf(_value, delimiter);
}

QString ZString::ltrim(QString charsEx){
    return ZString::ltrim(_value, charsEx);
}

QString ZString::rtrim(QString charsEx){
    return ZString::rtrim(_value, charsEx);
}

QString ZString::trim(QString charsEx){
    return ZString::trim(_value, charsEx);
}

QString ZString::reverse(){
    return ZString::reverse(_value);
}

QString ZString::lpad(uint width, QChar pad){
    return ZString::lpad(_value, width, pad);
}

QString ZString::rpad(uint width, QChar pad){
    return ZString::rpad(_value, width, pad);
}

QString ZString::upcase(){
    return ZString::upcase(_value);
}

QString ZString::downcase(){
    return ZString::downcase(_value);
}

QString ZString::sentenceCase(){
    return ZString::sentenceCase(_value);
}

QString ZString::titleCase(){
    return ZString::titleCase(_value);
}

QString ZString::squeeze(QChar chr){
    return ZString::squeeze(_value, chr);
}

QString ZString::lelide(int width, QString abbr){
    return ZString::lelide(_value, width, abbr);
}

QString ZString::relide(int width, QString abbr){
    return ZString::relide(_value, width, abbr);
}

QString ZString::elide(int width, QString abbr){
    return ZString::elide(_value, width, abbr);
}

QString ZString::lshift(uint num){
    return ZString::lshift(_value, num);
}

QString ZString::rshift(uint num){
    return ZString::rshift(_value, num);
}

QString ZString::concat(const QVariant &other){
    return ZString::concat(_value, other);
}

QString ZString::repeat(uint times){
    return ZString::repeat(_value, times);
}
