#include "zrubyscript.h"

VALUE zrb_property(VALUE self, VALUE mstring){
    char *methodString  = STR2CSTR(mstring);
    QVariant rv = zEvent->getProperty(QString(methodString));

    if(!rv.isValid() || rv.isNull())
        return Qnil;

    switch(rv.type()){
    case QMetaType::Bool:
        return (rv.toBool() ? Qtrue : Qfalse);

    case QMetaType::Int:
    case QMetaType::Long:
        return rb_int2inum(rv.toInt());

    case QMetaType::UInt:
    case QMetaType::ULong:
        return rb_uint2inum(rv.toUInt());

    case QMetaType::LongLong:
        return rb_ll2inum(rv.toLongLong());

    case QMetaType::ULongLong:
        return rb_ull2inum(rv.toULongLong());

    case QMetaType::Float:
    case QMetaType::Double:
        break;
    }

    return rb_str_new2(CSTR(rv.toString()));
}

VALUE zrb_grab_output(VALUE self){
    //_cZIOCapture = rb_define_class("ZIOCapture", rb_cObject);
    //rb_define_method(_cZIOCapture, "initialize", (VALUE(*)(...)),0);
}

ZRubyScript::ZRubyScript(const ZConfig &el, QObject *parent)
    : ZAbstractScript(el,this,parent)
{
    ruby_init();
    ruby_init_loadpath();

    zEvent->registerSlot(this, SLOT(exec()));

    parse(_config);
}

ZRubyScript::~ZRubyScript(){
}

void ZRubyScript::parse(const ZConfig &el){
    if(el.hasAttribute("src")){
        init();

        if(QFile::exists(el.attribute("src")))
            rb_load_file(CSTR(el.attribute("src")));
    }
}

void ZRubyScript::init(){
    _cZee = rb_define_class(ZEE_APPNAME, rb_cObject);
    rb_define_singleton_method(_cZee, "property", (VALUE(*)(...))&zrb_property, 1);
}

void ZRubyScript::lateInit(){
    z_log_debug("ZRubyScript: LATE INIT");
    if(_autorun)
        exec();
}

void ZRubyScript::exec(){
    ruby_exec();
}

void ZRubyScript::eval(QString code){
//    QString
}
