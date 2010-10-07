#ifndef ZRUBYSCRIPT_H
#define ZRUBYSCRIPT_H

#define ZCM_RUBYSCRIPT        "zee:ruby"

#include <ruby.h>
#include <QVariant>
#include <zabstractscript.h>

extern VALUE zrb_property(VALUE self, VALUE mstring);
extern VALUE zrb_grab_output(VALUE self);

class ZRubyScript : public ZAbstractScript
{
    Q_OBJECT

public:
    ZRubyScript(const ZConfig &el, QObject *parent=0);
    ~ZRubyScript();

public slots:
    void exec();
    void eval(QString code);

private:
    void parse(const ZConfig &el);
    void init();
    void lateInit();

private:
    VALUE _cZee;
    VALUE _cZIOCapture;
};

#endif // ZRUBYSCRIPT_H
