#ifndef ZSTYLE_H
#define ZSTYLE_H

#include <QObject>
#include <QTextStream>
#include <QFile>
#include <QRegExp>
#include <libzee/libzee.h>
#include <zutil.h>
#include <zstylesection.h>

class ZStyle : public QObject
{
    Q_OBJECT
public:
    ZStyle(QString filename, QObject *parent=0);
    ZStyle(QObject *parent=0);
    void loadFile(QString filename);
    QString styleSheet();
    QString baseStyleSheet();

private:
    void init();
    void parseData();

private:
    QList<ZStyleSection*> _sections;
    QString _filename;
    QString _basedata;
    ZString _data;
};

#endif // ZSTYLE_H
