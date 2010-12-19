#ifndef ZREGEXFORMATTER_H
#define ZREGEXFORMATTER_H

#define ZCM_FORMATTER_REGEX                 "regex"

#define ZFMT_METHOD_REGEX_MATCH             "match"
#define ZFMT_METHOD_REGEX_MATCH_FIRST       "match-first"
#define ZFMT_METHOD_REGEX_MATCH_LAST        "match-last"
#define ZFMT_METHOD_REGEX_MATCH_ALL         "match-all"
#define ZFMT_METHOD_REGEX_REPLACE           "replace"

#include <QRegExp>
#include <libzee/zstring.h>
#include <zabstractformatter.h>

class ZRegexFormatter : public ZAbstractFormatter
{
    Q_OBJECT

public:
    ZRegexFormatter(QObject *parent=0);

public slots:
    virtual QVariant transform(QVariant);

private:
    QVariant _match(QVariant in, QString pattern, int occurrence=1);
    QVariant _matchFirst(QVariant in, QString pattern);
    QVariant _matchLast(QVariant in, QString pattern);
    QVariant _matchAll(QVariant in, QString pattern, QString separator=QString());
    QVariant _replace(QVariant in, QString pattern, QString with);

private:
    static int _regexIndexInDirection(QRegExp&,QString,int,bool=true);
};

#endif // ZREGEXFORMATTER_H
