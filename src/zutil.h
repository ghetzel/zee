/******************************************************************************
*    This file is part of Zee.
*
*    Zee is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    Zee is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with Zee.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

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

#define ZSYM_SPACE      "space"
#define ZSYM_TAB        "tab"
#define ZSYM_DOT        "dot"
#define ZSYM_SLASH      "slash"
#define ZSYM_BSLASH     "backslash"
#define ZSYM_BTICK      "backtick"
#define ZSYM_TILDE      "tilde"
#define ZSYM_EXCLAIM    "exclaim"
#define ZSYM_AT         "at"
#define ZSYM_HASH       "hash"
#define ZSYM_DOLLAR     "dollar"
#define ZSYM_PERCENT    "percent"
#define ZSYM_CARAT      "carat"
#define ZSYM_AMPERSAND  "ampersand"
#define ZSYM_ASTERISK   "asterisk"
#define ZSYM_PAREN1     "paren1"
#define ZSYM_PAREN2     "paren2"
#define ZSYM_HYPHEN     "hyphen"
#define ZSYM_UNDERSCORE "underscore"
#define ZSYM_PLUS       "plus"
#define ZSYM_EQUALS     "equals"
#define ZSYM_BRACE1     "brace1"
#define ZSYM_BRACE2     "brace2"
#define ZSYM_SQUARE1    "square1"
#define ZSYM_SQUARE2    "square2"
#define ZSYM_PIPE       "pipe"
#define ZSYM_SEMICOLON  "semicolon"
#define ZSYM_COLON      "colon"
#define ZSYM_DQUOTE     "double-quote"
#define ZSYM_QUOTE      "quote"
#define ZSYM_LCARAT     "left-carat"
#define ZSYM_RCARAT     "right-carat"
#define ZSYM_COMMA      "comma"
#define ZSYM_QUESTION   "question"

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
#define CSTR(x)         qstrdup(STR(x).toLocal8Bit().data())
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

/*!
  Returns a printable version of \a symbol suitable for use in filenames
*/
  static QString trsym(QChar in);
};

#endif // ZUTIL_H
