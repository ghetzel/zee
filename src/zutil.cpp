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
    FILE* pipe = popen(CSTR(command), "r");
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

bool ZUtil::in(QString source, QString list){
    QStringList lst = list.split(QRegExp("\\W+"));
    return lst.contains(source);
}

QString ZUtil::trsym(QChar in){
    switch(in.toAscii()){
    case ' ':
	return ZSYM_SPACE;
    case '\t':
	return ZSYM_TAB;
    case '.':
	return ZSYM_DOT;
    case '/':
	return ZSYM_SLASH;
    case '\\':
	return ZSYM_BSLASH;
    case '`':
	return ZSYM_BTICK;
    case '~':
	return ZSYM_TILDE;
    case '!':
	return ZSYM_EXCLAIM;
    case '@':
	return ZSYM_AT;
    case '#':
	return ZSYM_HASH;
    case '$':
	return ZSYM_DOLLAR;
    case '%':
	return ZSYM_PERCENT;
    case '^':
	return ZSYM_CARAT;
    case '&':
	return ZSYM_AMPERSAND;
    case '*':
	return ZSYM_ASTERISK;
    case '(':
	return ZSYM_PAREN1;
    case ')':
	return ZSYM_PAREN2;
    case '-':
	return ZSYM_HYPHEN;
    case '_':
	return ZSYM_UNDERSCORE;
    case '+':
	return ZSYM_PLUS;
    case '=':
	return ZSYM_EQUALS;
    case '{':
	return ZSYM_BRACE1;
    case '}':
	return ZSYM_BRACE2;
    case '[':
	return ZSYM_SQUARE1;
    case ']':
	return ZSYM_SQUARE2;
    case '|':
	return ZSYM_PIPE;
    case ';':
	return ZSYM_SEMICOLON;
    case ':':
	return ZSYM_COLON;
    case '"':
	return ZSYM_DQUOTE;
    case '\'':
	return ZSYM_QUOTE;
    case '<':
	return ZSYM_LCARAT;
    case '>':
	return ZSYM_RCARAT;
    case ',':
	return ZSYM_COMMA;
    case '?':
	return ZSYM_QUESTION;
    }

    return QString(in);
}
