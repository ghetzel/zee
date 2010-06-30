#include "zutil.h"

ZUtil::ZLogLevel ZUtil::logLevel = ZUTL_DEFAULT_LOG_LEVEL;

void ZUtil::setLogLevel(ZLogLevel level)
{
  logLevel = level;
}

void ZUtil::output(QString output){
    cout << output.toAscii().data() << endl;
    flush(cout);
}

void ZUtil::log(QString output, ZLogLevel level){
  QString outpre;

//do not output messages above our level of verbosity
  if(level > logLevel)
    return;

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

  cerr << " [" << outpre.toAscii().data() << "]\t" << output.toAscii().data() << endl;
  flush(cerr);
}


bool ZUtil::hasFlag(ulong flag, ulong flags)
{
  z_log_debug("Find flag "+QVariant((int)flag).toString()+" in "+QVariant((int)flags).toString());
  return ((flags & flag) == flag);
}

QString ZUtil::exec(QString command){
    FILE* pipe = popen(command.toAscii().data(), "r");
    if (!pipe)
            return QString();
    char buffer[128];
    QString result;
    while(!feof(pipe)){
            if(fgets(buffer, 128, pipe) != NULL)
                    result += buffer;
    }
    pclose(pipe);
    return result;
}

QString ZUtil::execln(QString command, QString terminator){
    return ZUtil::exec(command).replace(QRegExp("[\n\r]"),terminator);
}
