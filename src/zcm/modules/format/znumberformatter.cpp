#include "znumberformatter.h"

ZNumberFormatter::ZNumberFormatter(QObject *parent)
    : ZAbstractFormatter(parent)
{
}

void ZNumberFormatter::transform(QVariant val){
    if(method() == ZFMT_METHOD_NUM_ROUND){ //!          round
        if(arg(0).isValid())
            emit ready(_round(val,arg(0).toInt()));
        else
            emit ready(_round(val));

    }else if(method() == ZFMT_METHOD_NUM_CURRENCY){ //! currency
        emit ready(_currency(val));

    }else if(method() == ZFMT_METHOD_NUM_CEIL){ //!     ceiling
        emit ready(_ceiling(val));

    }else if(method() == ZFMT_METHOD_NUM_FLOOR){ //!    floor
        emit ready(_floor(val));

    }else if(method() == ZFMT_METHOD_NUM_FIX){ //!      fix
        emit ready(_fix(val, arg(0).toInt()));

    }else if(method() == ZFMT_METHOD_NUM_ABS){ //!      abs
        emit ready(_abs(val));

    }else if(method() == ZFMT_METHOD_NUM_MIN){ //!      min
        emit ready(_min(val, arg(0)));

    }else if(method() == ZFMT_METHOD_NUM_MAX){ //!      max
        emit ready(_max(val, arg(0)));

    }else if(method() == ZFMT_METHOD_NUM_AVG){ //!      avg
        emit ready(_avg(val, arg(0)));

    }else if(method() == ZFMT_METHOD_NUM_RANGE){ //!    range
        emit ready(_range(val, arg(0)));

    }else if(method() == ZFMT_METHOD_NUM_ACOS){ //!     acos
        emit ready(_acos(val));

    }else if(method() == ZFMT_METHOD_NUM_ACOT){ //!     acot
        emit ready(_acot(val));

    }else if(method() == ZFMT_METHOD_NUM_ACSC){ //!     acsc
        emit ready(_acsc(val));

    }else if(method() == ZFMT_METHOD_NUM_ASEC){ //!     asec
        emit ready(_asec(val));

    }else if(method() == ZFMT_METHOD_NUM_ASIN){ //!     asin
        emit ready(_asin(val));

    }else if(method() == ZFMT_METHOD_NUM_ATAN){ //!     atan
        emit ready(_atan(val));

    }else if(method() == ZFMT_METHOD_NUM_COS){ //!      cos
        emit ready(_cos(val));

    }else if(method() == ZFMT_METHOD_NUM_COT){ //!      cot
        emit ready(_cot(val));

    }else if(method() == ZFMT_METHOD_NUM_CSC){ //!      csc
        emit ready(_csc(val));

    }else if(method() == ZFMT_METHOD_NUM_SEC){ //!      sec
        emit ready(_sec(val));

    }else if(method() == ZFMT_METHOD_NUM_SIN){ //!      sin
        emit ready(_sin(val));

    }else if(method() == ZFMT_METHOD_NUM_TAN){ //!      tan
        emit ready(_tan(val));

    }else if(method() == ZFMT_METHOD_NUM_SUM){ //!      sum
        emit ready(_sum(val, arg(0)));

    }else if(method() == ZFMT_METHOD_NUM_DIFF){ //!     difference
        emit ready(_difference(val, arg(0)));

    }else if(method() == ZFMT_METHOD_NUM_PROD){ //!     product
        emit ready(_product(val, arg(0)));

    }else if(method() == ZFMT_METHOD_NUM_QUOT){ //!     quotient
        emit ready(_quotient(val, arg(0)));

    }else if(method() == ZFMT_METHOD_NUM_MOD){ //!      mod
        emit ready(_modulus(val, arg(0)));

    }else if(method() == ZFMT_METHOD_NUM_EXP){ //!      exponent
        emit ready(_exponent(val, arg(0).toFloat()));

    }else if(method() == ZFMT_METHOD_NUM_LOG){ //!      log
        emit ready(_log(val, arg(0).toInt()));

    }else if(method() == ZFMT_METHOD_NUM_LN){ //!       ln
        emit ready(_ln(val));

    }else if(method() == ZFMT_METHOD_NUM_GCD){ //!      gcd (greatest cmn. denom.)
        emit ready(_gcd(val, arg(0)));

    }else if(method() == ZFMT_METHOD_NUM_LCM){ //!      lcm (least cmn. multiple)
        emit ready(_lcm(val, arg(0)));

    }else if(method() == ZFMT_METHOD_NUM_BASE){ //!     base (arbitrary)
        emit ready(_base(val, arg(0).toInt()));

    }else if(method() == ZFMT_METHOD_NUM_BIN){ //!      bin (base-10 to binary)
        emit ready(_bin(val));

    }else if(method() == ZFMT_METHOD_NUM_OCT){ //!      octal (base-10 to octal)
        emit ready(_octal(val));

    }else if(method() == ZFMT_METHOD_NUM_HEX){ //!      hex (base-10 to hex)
        emit ready(_hex(val));

    }else if(method() == ZFMT_METHOD_NUM_EVEN){ //!     event
        emit ready(_even(val));
    }else if(method() == ZFMT_METHOD_NUM_ODD){ //!      odd
        emit ready(_odd(val));
    //}else if(method() == ZFMT_METHOD_NUM_DERIV){ //!    derivative
    }else{
        emit ready(val);
    }
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

QVariant ZNumberFormatter::_even(QVariant in){
    return QVariant((in.toInt()%2 == 0));
}

QVariant ZNumberFormatter::_odd(QVariant in){
    return QVariant((in.toInt()%2 != 0));
}

QVariant ZNumberFormatter::_sin(QVariant in){
    return QVariant(qSin(in.toDouble()));
}

QVariant ZNumberFormatter::_cos(QVariant in){
    return QVariant(qCos(in.toDouble()));
}

QVariant ZNumberFormatter::_tan(QVariant in){
    return QVariant(qTan(in.toDouble()));
}

QVariant ZNumberFormatter::_sec(QVariant in){
    return QVariant(1.0/qCos(in.toDouble()));
}

QVariant ZNumberFormatter::_csc(QVariant in){
    return QVariant(1.0/qSin(in.toDouble()));
}

QVariant ZNumberFormatter::_cot(QVariant in){
    return QVariant(1.0/qTan(in.toDouble()));
}

QVariant ZNumberFormatter::_asin(QVariant in){
    return QVariant();
}

QVariant ZNumberFormatter::_acos(QVariant in){
    return QVariant();
}

QVariant ZNumberFormatter::_atan(QVariant in){
    return QVariant();
}

QVariant ZNumberFormatter::_asec(QVariant in){
    return QVariant();
}

QVariant ZNumberFormatter::_acsc(QVariant in){
    return QVariant();
}

QVariant ZNumberFormatter::_acot(QVariant in){
    return QVariant();
}

