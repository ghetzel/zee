#include "zrubyscript.h"

ZRubyScript::ZRubyScript(const ZConfig &el, QObject *parent)
    : QObject(parent),
      ZConfigurable(el,this)
{
    ruby_init();
    ruby_init_loadpath();
}

void ZRubyScript::parse(const ZConfig &el){
    if(el.hasAttribute("src")){
        initInterpreterEnv();

        if(QFile::exists(el.attribute("src")))
            rb_load_file(CSTR(el.attribute("src")));
    }
}

void ZRubyScript::initInterpreterEnv(){
    _cZee = rb_define_class(ZEE_APPNAME, rb_cObject);

    rb_define_singleton_method(_cZee, "property", &ZRubyScript::zrb_property, 1);
}

VALUE ZRubyScript::zrb_property(...){
    va_list args;
    va_start(args,1);
    char *methodString = va_arg(args,char*);
    va_end(args);
    return rb_str_new2(methodString);
}
