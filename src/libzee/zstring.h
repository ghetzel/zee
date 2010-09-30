#ifndef ZSTRING_H
#define ZSTRING_H

#include <qmath.h>
#include <QObject>
#include <QVariant>
#include <QRegExp>

class ZString : public QString
{
public:
    ZString(ZString &other);
    ZString(QString &other);
    QString toQString();
    QString left(uint len);
    QString right(uint len);
    QString leftOf(QString delimiter);
    QString rightOf(QString delimiter);
    QString ltrim(QString charsEx="\\w+");
    QString rtrim(QString charsEx="\\w+");
    QString trim(QString charsEx="\\w+");
    QString reverse();
    QString lpad(uint width, QChar pad=' ');
    QString rpad(uint width, QChar pad=' ');
    QString upcase();
    QString downcase();
    QString sentenceCase();
    QString titleCase();
    QString squeeze(QChar chr='\0');
    QString lelide(int width, QString abbr="...");
    QString relide(int width, QString abbr="...");
    QString elide(int width, QString abbr="...");
    QString lshift(uint num);
    QString rshift(uint num);
    QString concat(const QVariant &other);
    QString repeat(uint times);

public:
    static QString left(QVariant in, uint len);
    static QString right(QVariant in, uint len);
    static QString leftOf(QVariant in, QString delimiter);
    static QString rightOf(QVariant in, QString delimiter);
    static QString ltrim(QVariant in, QString charsEx="\\w+");
    static QString rtrim(QVariant in, QString charsEx="\\w+");
    static QString trim(QVariant in, QString charsEx="\\w+");
    static QString reverse(QVariant in);
    static QString lpad(QVariant in, uint width, QChar pad=' ');
    static QString rpad(QVariant in, uint width, QChar pad=' ');
    static QString upcase(QVariant in);
    static QString downcase(QVariant in);
    static QString sentenceCase(QVariant in);
    static QString titleCase(QVariant in);
    static QString squeeze(QVariant in, QChar chr='\0');
    static QString lelide(QVariant in, int width, QString abbr="...");
    static QString relide(QVariant in, int width, QString abbr="...");
    static QString elide(QVariant in, int width, QString abbr="...");
    static QString lshift(QVariant in, uint num);
    static QString rshift(QVariant in, uint num);
    static QString concat(QVariant in, QVariant other);
    static QString repeat(QVariant in, uint times);

private:
    QString _value;
};

#endif // ZSTRING_H
