// g++ -orubyembed -I. -I/usr/lib64/ruby/1.8/x86_64-linux -lruby rubyembed.cpp

#include <ruby.h>
#include <iostream>

using namespace std;

VALUE testBind1(VALUE bits){
	return rb_str_new2("test bind 1");
}

int main(int argc, char *argv[])
{
	ruby_init();
	ruby_init_loadpath();
	rb_load_file("test.rb");

	VALUE c_Zee = rb_define_class("Zee", rb_cObject);
	rb_define_singleton_method(c_Zee, "appname", &testBind1, 0);
	
	ruby_run();
//	ruby_finalize();
	return 0;
}
