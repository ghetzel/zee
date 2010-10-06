#ifndef ZRUBYSCRIPT_H
#define ZRUBYSCRIPT_H

#define ZSCRIPT_RUBY        "zee:ruby"

#include <ruby.h>
#include <stdarg.h>
#include <QVariant>
#include <zeventmanager.h>
#include <zconfigurable.h>

class ZRubyScript : public QObject, public ZConfigurable
{
public:
    ZRubyScript(const ZConfig &el, QObject *parent=0);

public:
    static VALUE zrb_property(...);

private:
    void parse(const ZConfig &el);
    void initInterpreterEnv();

private:
    VALUE _cZee;
};

#endif // ZRUBYSCRIPT_H
