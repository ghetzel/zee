#ifndef ZRUBYSCRIPT_H
#define ZRUBYSCRIPT_H

#define ZCM_RUBYSCRIPT        "zee:ruby"

#include <ruby.h>
#include <QVariant>
#include <zabstractscript.h>

class ZRubyScript : public ZAbstractScript
{
    Q_OBJECT

public:
    ZRubyScript(const ZConfig &el, QObject *parent=0);
    ~ZRubyScript();

public slots:
    void exec();

private:
    void parse(const ZConfig &el);
    void init();
    void lateInit();

private:
    VALUE _cZee;
};

#endif // ZRUBYSCRIPT_H
