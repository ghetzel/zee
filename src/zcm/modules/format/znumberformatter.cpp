#include "znumberformatter.h"

ZNumberFormatter::ZNumberFormatter(QObject *parent)
    : ZAbstractFormatter(parent)
{
}

QVariant ZNumberFormatter::transform(QVariant val){
    if(method() == ZFMT_METHOD_NUM_ROUND){ //!          round
        if(arg(0).isValid())
            return _round(val,arg(0).toInt());
        else
            return _round(val);

    }else if(method() == ZFMT_METHOD_NUM_CURRENCY){ //! currency
        return _currency(val);

    }else if(method() == ZFMT_METHOD_NUM_CEIL){ //!     ceiling
        return _ceiling(val);

    }else if(method() == ZFMT_METHOD_NUM_FLOOR){ //!    floor
        return _floor(val);

    }else if(method() == ZFMT_METHOD_NUM_FIX){ //!      fix
        return _fix(val, arg(0).toInt());

    }else if(method() == ZFMT_METHOD_NUM_ABS){ //!      abs
        return _abs(val);

    }else if(method() == ZFMT_METHOD_NUM_MIN){ //!      min
        return _min(val, arg(0));

    }else if(method() == ZFMT_METHOD_NUM_MAX){ //!      max
        return _max(val, arg(0));

    }else if(method() == ZFMT_METHOD_NUM_AVG){ //!      avg
        return _avg(val, arg(0));

    }else if(method() == ZFMT_METHOD_NUM_RANGE){ //!    range
        return _range(val, arg(0));

    }else if(method() == ZFMT_METHOD_NUM_ACOS){ //!     acos
        return _acos(val);

    }else if(method() == ZFMT_METHOD_NUM_ACOT){ //!     acot
        return _acot(val);

    }else if(method() == ZFMT_METHOD_NUM_ACSC){ //!     acsc
        return _acsc(val);

    }else if(method() == ZFMT_METHOD_NUM_ASEC){ //!     asec
        return _asec(val);

    }else if(method() == ZFMT_METHOD_NUM_ASIN){ //!     asin
        return _asin(val);

    }else if(method() == ZFMT_METHOD_NUM_ATAN){ //!     atan
        return _atan(val);

    }else if(method() == ZFMT_METHOD_NUM_COS){ //!      cos
        return _cos(val);

    }else if(method() == ZFMT_METHOD_NUM_COT){ //!      cot
        return _cot(val);

    }else if(method() == ZFMT_METHOD_NUM_CSC){ //!      csc
        return _csc(val);

    }else if(method() == ZFMT_METHOD_NUM_SEC){ //!      sec
        return _sec(val);

    }else if(method() == ZFMT_METHOD_NUM_SIN){ //!      sin
        return _sin(val);

    }else if(method() == ZFMT_METHOD_NUM_TAN){ //!      tan
        return _tan(val);

    }else if(method() == ZFMT_METHOD_NUM_SUM){ //!      sum
        return _sum(val, arg(0));

    }else if(method() == ZFMT_METHOD_NUM_DIFF){ //!     difference
        return _difference(val, arg(0));

    }else if(method() == ZFMT_METHOD_NUM_PROD){ //!     product
        return _product(val, arg(0));

    }else if(method() == ZFMT_METHOD_NUM_QUOT){ //!     quotient
        return _quotient(val, arg(0));

    }else if(method() == ZFMT_METHOD_NUM_MOD){ //!      mod
        return _modulus(val, arg(0));

    }else if(method() == ZFMT_METHOD_NUM_EXP){ //!      exponent
        return _exponent(val, arg(0).toFloat());

    }else if(method() == ZFMT_METHOD_NUM_LOG){ //!      log
        return _log(val, arg(0).toInt());

    }else if(method() == ZFMT_METHOD_NUM_LN){ //!       ln
        return _ln(val);

    }else if(method() == ZFMT_METHOD_NUM_GCD){ //!      gcd (greatest cmn. denom.)
        return _gcd(val, arg(0));

    }else if(method() == ZFMT_METHOD_NUM_LCM){ //!      lcm (least cmn. multiple)
        return _lcm(val, arg(0));

    }else if(method() == ZFMT_METHOD_NUM_BASE){ //!     base (arbitrary)
        return _base(val, arg(0).toInt());

    }else if(method() == ZFMT_METHOD_NUM_BIN){ //!      bin (base-10 to binary)
        return _bin(val);

    }else if(method() == ZFMT_METHOD_NUM_OCT){ //!      octal (base-10 to octal)
        return _octal(val);

    }else if(method() == ZFMT_METHOD_NUM_HEX){ //!      hex (base-10 to hex)
        return _hex(val);

    }else if(method() == ZFMT_METHOD_NUM_EVEN){ //!     event
        return _even(val);
    }else if(method() == ZFMT_METHOD_NUM_ODD){ //!      odd
        return _odd(val);
    //}else if(method() == ZFMT_METHOD_NUM_DERIV){ //!    derivative
    }

    return val;
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

