#include "znumberformatter.h"

ZNumberFormatter::ZNumberFormatter(QObject *parent)
    : ZAbstractFormatter(parent)
{
}

void ZNumberFormatter::transform(QVariant val){

}


QVariant ZNumberFormatter::_round(QVariant in, int places){
    qreal rv = in.toDouble();
    qreal multiplier = qPow(10,places);
    rv *= multiplier;
    rv = qRound(rv);
    return QVariant(rv/multiplier);
}

QVariant ZNumberFormatter::_currency(QVariant in){
    return _round(in,2);
}

QVariant ZNumberFormatter::_ceiling(QVariant in){
    return QVariant(qCeil(in.toDouble()));
}

QVariant ZNumberFormatter::_floor(QVariant in){
    return QVariant(qFloor(in.toDouble()));
}

QVariant ZNumberFormatter::_fix(QVariant in, int places){
    return in;
}

QVariant ZNumberFormatter::_abs(QVariant in){
    return QVariant(qAbs(in.toDouble()));
}

QVariant ZNumberFormatter::_min(QVariant in, QVariant other){
    return QVariant(qMin(in.toDouble(), other.toDouble()));
}

QVariant ZNumberFormatter::_max(QVariant in, QVariant other){
    return QVariant(qMax(in.toDouble(), other.toDouble()));
}

QVariant ZNumberFormatter::_avg(QVariant in, QVariant other){
    return in;
}

QVariant ZNumberFormatter::_range(QVariant in, QVariant other){
    return QVariant(qAbs(other.toDouble()-in.toDouble()));
}

QVariant ZNumberFormatter::_sum(QVariant in, QVariant other){
    return QVariant(in.toDouble()+other.toDouble());
}

QVariant ZNumberFormatter::_difference(QVariant in, QVariant other){
    return QVariant(in.toDouble()-other.toDouble());
}

QVariant ZNumberFormatter::_product(QVariant in, QVariant other){
    return QVariant(in.toDouble()*other.toDouble());
}

QVariant ZNumberFormatter::_quotient(QVariant in, QVariant other){
    if(other.toDouble() == 0)
        return QVariant();
    return QVariant(in.toDouble()/other.toDouble());
}

QVariant ZNumberFormatter::_modulus(QVariant in, QVariant other){
    if(other.toDouble() == 0)
        return QVariant();
    return QVariant(in.toInt() % other.toInt());
}

QVariant ZNumberFormatter::_exponent(QVariant in, float power){
    return QVariant(qPow(in.toDouble(), power));
}

QVariant ZNumberFormatter::_log(QVariant in, int base){
    return in;
}

QVariant ZNumberFormatter::_ln(QVariant in){
    return QVariant(qLn(in.toDouble()));
}

QVariant ZNumberFormatter::_gcd(QVariant in, QVariant other){
    return in;
}

QVariant ZNumberFormatter::_lcm(QVariant in, QVariant other){
    return in;
}

QVariant ZNumberFormatter::_base(QVariant in, int toBase, int fromBase){
    QString val = in.toString();
    char tokens[36] = {'0','1','2','3','4','5','6','7',     // base 8
                       '8','9','A','B','C','D','E','F',     // base 16
                       'G','H','I','J','K','L','M','N',     // base 24
                       'O','P','Q','R','S','T','U','V',     // base 32
                       'W','X','Y','Z'};                    // base 36
    QString rv;
    int remain = 0;
    long input = in.toInt();

    do{
        remain = input % toBase;
        input /= toBase;
        rv.prepend(tokens[remain]);
        remain -= toBase;
    }while(input > 0);

    return QVariant(rv);
}

QVariant ZNumberFormatter::_bin(QVariant in, int fromBase){
    return _base(in,2,fromBase);
}

QVariant ZNumberFormatter::_octal(QVariant in, int fromBase){
    return _base(in,8,fromBase);
}

QVariant ZNumberFormatter::_hex(QVariant in, int fromBase){
    return _base(in,16,fromBase);
}

QVariant ZNumberFormatter::_even(QVariant in){}

QVariant ZNumberFormatter::_odd(QVariant in){}

QVariant ZNumberFormatter::_sin(QVariant in){}

QVariant ZNumberFormatter::_cos(QVariant in){}

QVariant ZNumberFormatter::_tan(QVariant in){}

QVariant ZNumberFormatter::_sec(QVariant in){}

QVariant ZNumberFormatter::_csc(QVariant in){}

QVariant ZNumberFormatter::_cot(QVariant in){}

QVariant ZNumberFormatter::_asin(QVariant in){}

QVariant ZNumberFormatter::_acos(QVariant in){}

QVariant ZNumberFormatter::_atan(QVariant in){}

QVariant ZNumberFormatter::_asec(QVariant in){}

QVariant ZNumberFormatter::_acsc(QVariant in){}

QVariant ZNumberFormatter::_acot(QVariant in){}

