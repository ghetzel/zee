#include "main.h"

int main(int argc, char *argv[])
{
  Zee zee(argc, argv);
  //ZeeAdaptor adaptor(&zee);
  return zee.exec();
}
