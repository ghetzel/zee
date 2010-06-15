#include "zutil.h"

ZUtil::ZLogLevel ZUtil::logLevel = ZUTL_DEFAULT_LOG_LEVEL;

void ZUtil::setLogLevel(ZLogLevel level)
{
  logLevel = level;
}

void ZUtil::log(QString output, ZLogLevel level){
  QString outpre;

  //! \todo re-enable when constant debugging isn't happening
////do not output messages above our level of verbosity
//  if(level > logLevel)
//    return;

  switch(level){
  case LogNone:
    //return;
  case LogDebug:
    outpre = "DD";
    break;
  case LogInfo:
    outpre = "--";
    break;
  case LogWarning:
    outpre = "WW";
    break;
  case LogError:
    outpre = "EE";
    break;
  case LogCritical:
    outpre = "!!";
    break;
  }

  cout << " [" << outpre.toAscii().data() << "]\t" << output.toAscii().data() << endl;
  flush(cout);
}


bool ZUtil::hasFlag(ulong flag, ulong flags)
{
  z_log_debug("Find flag "+QVariant((int)flag).toString()+" in "+QVariant((int)flags).toString());
  return ((flags & flag) == flag);
}
