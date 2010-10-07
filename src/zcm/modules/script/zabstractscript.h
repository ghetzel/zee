#ifndef ZABSTRACTSCRIPT_H
#define ZABSTRACTSCRIPT_H

#include <QObject>
#include <zconfigurable.h>
#include <zeventmanager.h>
#include <zui/zuiutils.h>

class ZAbstractScript : public QObject, public ZConfigurable
{
    Q_OBJECT
public:
    ZAbstractScript(const ZConfig &el, QObject *self, QObject *parent=0);

public slots:
    virtual void exec()=0;

protected:
    bool _autorun;

private:
    void parse(const ZConfig &el);
};

#endif // ZABSTRACTSCRIPT_H
