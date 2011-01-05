#ifndef ZSSPARSER_H
#define ZSSPARSER_H

#include <QObject>
#include <QTextStream>
#include <QFile>
#include <QRegExp>
#include <libzee/libzee.h>
#include <zutil.h>

class ZSSParser : public QObject
{
    Q_OBJECT
public:
    ZSSParser(QString filename, QObject *parent=0);
    ZSSParser(QObject *parent=0);
    void loadFile(QString filename);

private:
    void init();
    void parseData();

private:
    QString _filename;
    QString _basedata;
    ZString _data;
};

#endif // ZSSPARSER_H
