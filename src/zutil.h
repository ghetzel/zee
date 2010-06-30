#ifndef ZUTIL_H
#define ZUTIL_H

#include <iostream>
#include <QtGlobal>
#include <QtDebug>
#include <QString>
#include <QVariant>
#include <QFile>
#include <QRegExp>
#include <QTextStream>

#define ZUTL_DEFAULT_LOG_LEVEL   ZUtil::LogDebug

#define ZEE_APPNAME     "Zee"
#define ZEE_OBJNAME     "zee"
#define ZEE_PROGNAME    "zee"

#define z_out(x)        ZUtil::output(x);
#define z_log(x)        ZUtil::log(x)
#define z_log_error(x)  ZUtil::log(x,ZUtil::LogError)
#define z_log_debug(x)  ZUtil::log(x,ZUtil::LogDebug)
#define z_log_warn(x)   ZUtil::log(x,ZUtil::LogWarning)
#define z_log_crit(x)   ZUtil::log(x,ZUtil::LogCritical)

#define CAST(t,v)       static_cast<t>(v)
#define DCAST(t,v)      dynamic_cast<t>(v)
#define RECAST(t,v)     reinterpret_cast<t>(v)
#define CCAST(t,v)      const_cast<t>(v)
#define QCAST(t,v)      qobject_cast<t>(v)

#define	STR(x)		QVariant(x).toString()
#define CSTR(x)         qstrdup(STR(x).toAscii().data())
#define METHODNAME(x)	QString(x).section("(",0,0)
#define METHODARGS(x)	QString(x).section("(",1,1).section(")",0,0)
#define DETYPESIG(x)	QString(x).right(QString(x).length()-1)
#define CALLALIAS(x)    QString(x).section(".",-1,-1)
#define SIGNAME(x)      DETYPESIG(METHODNAME(x))
#define SLOTNAME(x)     DETYPESIG(METHODNAME(x))
#define ZSIGNAL(x)      CSTR("2"+QString(x))
#define ZSLOT(x)        CSTR("1"+QString(x))

#ifndef Q_PI
static const double Q_PI   = 3.14159265358979323846;

#define RADIANS(x)      (x)*(Q_PI/180)
#define DEGREES(x)      (x)*(180/Q_PI)
#endif

using namespace std;

/*!
  \class ZUtil
  \ingroup zeeapp
  \brief Contains utility functions for the application and its plugins.
*/
class ZUtil{

public:
  enum ZLogLevel{
    LogNone = 1,
    LogCritical = 2,
    LogError = 3,
    LogWarning = 4,
    LogInfo = 5,
    LogDebug = 6
  };

  static ZLogLevel logLevel;

public:
  static void init();

/*!
  Sets the \a level of log verbosity
*/
  static void setLogLevel(ZLogLevel level = ZUTL_DEFAULT_LOG_LEVEL);

/*!
  Logs the string \a output to the standard error with priority \a level
*/
  static void log(QString output, ZLogLevel level = ZUTL_DEFAULT_LOG_LEVEL);

/*!
  Outputs \a output to standard output
*/
  static void output(QString output);

/*!
  Returns whether \a flag is present in \a flags
*/
  static bool hasFlag(ulong flag, ulong flags);

/*!
  Returns the output of \a command
*/
  static QString exec(QString command);

/*!
  Returns the output of \a command with all line breaks removed
*/
  static QString execln(QString command, QString terminator="");
};

#endif // ZUTIL_H
