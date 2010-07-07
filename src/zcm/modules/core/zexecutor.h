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
    Q_PROPERTY(QString lastOutput READ lastOutput)
public:
    ZExecutor(const ZConfig &el, QObject *parent=0);
    ~ZExecutor();
    QString lastOutput();

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
    QString _lastOutput;
};

#endif // ZEXECUTOR_H
