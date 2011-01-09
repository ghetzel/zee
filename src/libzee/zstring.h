#ifndef ZSTRING_H
#define ZSTRING_H

#include <qmath.h>
#include <QtDebug>
#include <QObject>
#include <QVariant>
#include <QRegExp>

class ZString : public QString
{
public:
    ZString();
    ZString(const ZString &other);
    ZString(const QString &other);
    ZString(const char *other);
    ZString& operator=(const ZString &other);
    ZString& operator=(const QString &other);
    ZString& operator=(const char *other);
    QString toQString();

public:
    ZString left(uint len);
    ZString right(uint len);
    ZString leftOf(QString delimiter);
    ZString leftOfLast(QString delimiter);
    ZString rightOf(QString delimiter);
    ZString rightOfLast(QString delimiter);
    ZString ltrim(QString charsEx="\\w+");
    ZString rtrim(QString charsEx="\\w+");
    ZString trim(QString charsEx="\\w+");
    ZString reverse();
    ZString lpad(uint width, QChar pad=' ');
    ZString rpad(uint width, QChar pad=' ');
    ZString upcase();
    ZString downcase();
    ZString sentenceCase();
    ZString titleCase();
    ZString squeeze(QChar chr='\0');
    ZString lelide(int width, QString abbr="...");
    ZString relide(int width, QString abbr="...");
    ZString elide(int width, QString abbr="...");
    ZString lshift(uint num);
    ZString rshift(uint num);
    ZString concat(const QVariant &other);
    ZString repeat(uint times);
    ZString substring(int beginIndex, int length);
    ZString find(QString subject);
    ZString find(QRegExp pattern);
    float fromPercent(qreal upper=100.0, qreal lower=0.0);
    bool match(QRegExp &pattern);

public:
    static ZString left(QVariant in, uint len);
    static ZString right(QVariant in, uint len);
    static ZString leftOf(QVariant in, QString delimiter);
    static ZString leftOfLast(QVariant in, QString delimiter);
    static ZString rightOf(QVariant in, QString delimiter);
    static ZString rightOfLast(QVariant in, QString delimiter);
    static ZString ltrim(QVariant in, QString charsEx="[\\s]*");
    static ZString rtrim(QVariant in, QString charsEx="[\\s]*");
    static ZString trim(QVariant in, QString charsEx="[\\s]*");
    static ZString reverse(QVariant in);
    static ZString lpad(QVariant in, uint width, QChar pad=' ');
    static ZString rpad(QVariant in, uint width, QChar pad=' ');
    static ZString upcase(QVariant in);
    static ZString downcase(QVariant in);
    static ZString sentenceCase(QVariant in);
    static ZString titleCase(QVariant in);
    static ZString squeeze(QVariant in, QChar chr='\0');
    static ZString lelide(QVariant in, int width, QString abbr="...");
    static ZString relide(QVariant in, int width, QString abbr="...");
    static ZString elide(QVariant in, int width, QString abbr="...");
    static ZString lshift(QVariant in, uint num);
    static ZString rshift(QVariant in, uint num);
    static ZString concat(QVariant in, QVariant other);
    static ZString repeat(QVariant in, uint times);
    static ZString substring(QVariant in, int beginIndex, int length);
    static ZString find(QVariant in, QString subject);
    static ZString find(QVariant in, QRegExp pattern);
    static float fromPercent(ZString in, qreal upper=100.0, qreal lower=0.0);
    static bool match(QVariant in, QRegExp &pattern);

private:
    void _setText(const ZString &other);
    void _setText(const QString &other);
    void _setText(const char *other);
};

Q_DECLARE_METATYPE(ZString);

#endif // ZSTRING_H
