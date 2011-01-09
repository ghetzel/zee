#ifndef ZSTYLE_H
#define ZSTYLE_H

#include <QObject>
#include <QTextStream>
#include <QFile>
#include <QRegExp>
#include <libzee/libzee.h>
#include <zutil.h>
#include <zeventmanager.h>
#include <zstylesection.h>

#define zStyle                      ZStyle::instance()

class ZStyle : public QObject
{
    Q_OBJECT
public:
    ZStyle(QString filename, QObject *parent=0);
    ZStyle(QObject *parent=0);
    static void initialize(ZStyle *instance=0);
    static ZStyle *instance();
    ZStyleSection &getSection(int id);
    void loadFile(QString filename);
    QString styleSheet();
    QString baseStyleSheet();

signals:
    void stylesheetChanged();

private:
    void init();
    void parseData();

private:
    static ZStyle *_instance;
    QList<ZStyleSection*> _sections;
    QString _filename;
    QString _basedata;
    ZString _data;
};

#endif // ZSTYLE_H
