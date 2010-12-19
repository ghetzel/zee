#ifndef ZNUMBERFORMATTER_H
#define ZNUMBERFORMATTER_H

#define ZCM_FORMATTER_NUMBER        "number"

#define ZFMT_METHOD_NUM_ROUND       "round"
#define ZFMT_METHOD_NUM_CURRENCY    "currency"
#define ZFMT_METHOD_NUM_CEIL        "ceiling"
#define ZFMT_METHOD_NUM_FLOOR       "floor"
#define ZFMT_METHOD_NUM_FIX         "fix"
#define ZFMT_METHOD_NUM_ABS         "abs"
#define ZFMT_METHOD_NUM_MIN         "min"
#define ZFMT_METHOD_NUM_MAX         "max"
#define ZFMT_METHOD_NUM_AVG         "avg"
#define ZFMT_METHOD_NUM_RANGE       "range"
#define ZFMT_METHOD_NUM_ACOS        "acos"
#define ZFMT_METHOD_NUM_ACOT        "acot"
#define ZFMT_METHOD_NUM_ACSC        "acsc"
#define ZFMT_METHOD_NUM_ASEC        "asec"
#define ZFMT_METHOD_NUM_ASIN        "asin"
#define ZFMT_METHOD_NUM_ATAN        "atan"
#define ZFMT_METHOD_NUM_COS         "cos"
#define ZFMT_METHOD_NUM_COT         "cot"
#define ZFMT_METHOD_NUM_CSC         "csc"
#define ZFMT_METHOD_NUM_SEC         "sec"
#define ZFMT_METHOD_NUM_SIN         "sin"
#define ZFMT_METHOD_NUM_TAN         "tan"
#define ZFMT_METHOD_NUM_SUM         "sum"
#define ZFMT_METHOD_NUM_DIFF        "difference"
#define ZFMT_METHOD_NUM_PROD        "product"
#define ZFMT_METHOD_NUM_QUOT        "quotient"
#define ZFMT_METHOD_NUM_MOD         "mod"
#define ZFMT_METHOD_NUM_EXP         "exponent"
#define ZFMT_METHOD_NUM_LOG         "log"
#define ZFMT_METHOD_NUM_LN          "ln"
#define ZFMT_METHOD_NUM_GCD         "gcd"
#define ZFMT_METHOD_NUM_LCM         "lcm"
#define ZFMT_METHOD_NUM_BASE        "base"
#define ZFMT_METHOD_NUM_BIN         "bin"
#define ZFMT_METHOD_NUM_OCT         "octal"
#define ZFMT_METHOD_NUM_HEX         "hex"
#define ZFMT_METHOD_NUM_EVEN        "even"
#define ZFMT_METHOD_NUM_ODD         "odd"
#define ZFMT_METHOD_NUM_DERIV       "derivative"

#include <zabstractformatter.h>
#include <qmath.h>

class ZNumberFormatter : public ZAbstractFormatter
{
    Q_OBJECT
public:
    ZNumberFormatter(QObject *parent=0);

public slots:
    virtual QVariant transform(QVariant);

private:
    QVariant _round(QVariant in, int places=0);
    QVariant _currency(QVariant in);
    QVariant _ceiling(QVariant in);
    QVariant _floor(QVariant in);
    QVariant _fix(QVariant in, int places);
    QVariant _abs(QVariant in);
    QVariant _min(QVariant in, QVariant other);
    QVariant _max(QVariant in, QVariant other);
    QVariant _avg(QVariant in, QVariant other);
    QVariant _range(QVariant in, QVariant other);
    QVariant _sum(QVariant in, QVariant other);
    QVariant _difference(QVariant in, QVariant other);
    QVariant _product(QVariant in, QVariant other);
    QVariant _quotient(QVariant in, QVariant other);
    QVariant _modulus(QVariant in, QVariant other);
    QVariant _exponent(QVariant in, float power);
    QVariant _log(QVariant in, int base=10);
    QVariant _ln(QVariant in);
    QVariant _gcd(QVariant in, QVariant other);
    QVariant _lcm(QVariant in, QVariant other);
    QVariant _base(QVariant in, int toBase, int fromBase=10);
    QVariant _bin(QVariant in, int fromBase=10);
    QVariant _octal(QVariant in, int fromBase=10);
    QVariant _hex(QVariant in, int fromBase=10);
    QVariant _even(QVariant in);
    QVariant _odd(QVariant in);
    QVariant _sin(QVariant in);
    QVariant _cos(QVariant in);
    QVariant _tan(QVariant in);
    QVariant _sec(QVariant in);
    QVariant _csc(QVariant in);
    QVariant _cot(QVariant in);
    QVariant _asin(QVariant in);
    QVariant _acos(QVariant in);
    QVariant _atan(QVariant in);
    QVariant _asec(QVariant in);
    QVariant _acsc(QVariant in);
    QVariant _acot(QVariant in);
};

#endif // ZNUMBERFORMATTER_H
