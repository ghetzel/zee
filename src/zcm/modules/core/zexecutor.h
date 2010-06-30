#ifndef ZEXECUTOR_H
#define ZEXECUTOR_H

#define ZCM_EXECUTOR    "zee:executor"

#include <QString>
#include <zutil.h>
#include <zconfigurable.h>
#include <zeventmanager.h>

class ZExecutor : public QObject, public ZConfigurable
{
    Q_OBJECT
public:
    ZExecutor(const ZConfig &el, QObject *parent=0);
    ~ZExecutor();

public slots:
    void exec();
    void setCommand(QString);

signals:
    void executed(QString);
    void commandChanged(QString,QString="");

private:
    void parse(const ZConfig &el);

private:
    QString _command;
    QString _oneLine;
};

#endif // ZEXECUTOR_H
