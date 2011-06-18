#ifndef ZSTYLE_H
#define ZSTYLE_H

#include <QObject>
#include <QTextStream>
#include <QFile>
#include <QRegExp>
#include <libzee/libzee.h>
#include <zutil.h>
#include <zeventmanager.h>
#include <zui/zstylesection.h>

#define zStyle                      ZStyleParser::instance()

class ZStyleParser : public QObject
{
    Q_OBJECT
public:
    ZStyleParser(QString filename, QObject *parent=0);
    ZStyleParser(QObject *parent=0);
    static void initialize(ZStyleParser *instance=0);
    static ZStyleParser *instance();
    void loadFile(QString filename);
    QString styleSheet();
    QString baseStyleSheet();

signals:
    void stylesheetChanged();

private:
    void init();
    void parseData();

private:
    static ZStyleParser *_instance;
    QList<ZStyleSection*> _sections;
    QString _filename;
    QString _basedata;
    QString _data;
};

#endif // ZSTYLE_H
