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

#include "zee.h"

Zee *Zee::_app = 0;

Zee::Zee(int argc, char *argv[])
    : QApplication(argc, argv){
    _app = this;

    init();
}

Zee *Zee::instance(){
    return _app;
}

QVariant Zee::arg(QString key){
    return _arguments.value(key);
}

bool Zee::hasArg(QString key){
    return _arguments.value(key).isValid();
}

void Zee::init()
{
    setObjectName(ZEE_OBJNAME);
    setApplicationName(ZEE_APPNAME);
    parseArguments();

    zEvent->registerSignal(this,SIGNAL(styleReloaded()));
    zEvent->registerSignal(this,SIGNAL(aboutToQuit()));
    zEvent->registerSignal(this,SIGNAL(lastWindowClosed()));
    zEvent->registerSignal(this,SIGNAL(unixSignal(int)));
    zEvent->registerSignal(this, SIGNAL(loadComplete()));

    zEvent->registerSlot(this,SLOT(closeAllWindows()));
    zEvent->registerSlot(this,SLOT(quit()));
    zEvent->registerSlot(this,SLOT(reloadStyleSheet()));
    zEvent->registerSlot(this,SLOT(setStyleSheet(QString)));
    zEvent->registerSlot(this,SLOT(output(QString)));
    zEvent->registerSlot(this,SLOT(log(QString)));
    zEvent->registerSlot(this,SLOT(logWarning(QString)));
    zEvent->registerSlot(this,SLOT(logError(QString)));
    zEvent->registerSlot(this,SLOT(logCritical(QString)));
    zEvent->registerSlot(this,SLOT(logDebug(QString)));

    //handle log verbosity setting
    if(hasArg("log-verbosity")){
        switch(arg("log-verbosity").toInt())
        {
        case 0:
            ZUtil::setLogLevel(ZUtil::LogNone);
            break;
        case 1:
            ZUtil::setLogLevel(ZUtil::LogCritical);
            break;
        case 2:
            ZUtil::setLogLevel(ZUtil::LogError);
            break;
        case 3:
            ZUtil::setLogLevel(ZUtil::LogWarning);
            break;
        case 4:
            ZUtil::setLogLevel(ZUtil::LogInfo);
            break;
        case 5:
            ZUtil::setLogLevel(ZUtil::LogDebug);
            break;
        default:
            ZUtil::setLogLevel(ZUtil::LogDebug);
        }
    }

    //setup config search paths
    QDir::setSearchPaths(ZEE_CFG_KEY,
                         QStringList(QDir::homePath()+"/"+ZEE_CFG_DIR+"/"+
                                     arg("program").toString()+"/"));
    z_log_debug("Zee: Search Path = "+STR(QDir::homePath()+"/"+ZEE_CFG_DIR+"/"+
                                         arg("program").toString()+"/"));
    reloadStyleSheet();
    parseUI();

    if(hasArg("debug-style")){
        QTimer *styleTimer = new QTimer(this);
        int intv = qAbs(arg("debug-style").toInt())*1000;

        if(intv < 1000) // if not specified or less than 1s, set to default interval
            intv = 3000;

        connect(styleTimer, SIGNAL(timeout()), this, SLOT(reloadStyleSheet()));
        styleTimer->start(intv);
    }

//  let's get this show on the road...
    foreach(QWidget *w, qApp->topLevelWidgets())
        if(w->isVisible())
            w->show();
}


void Zee::parseArguments(){
    QStringList args = arguments();

    // store the program name
    _arguments.insert("program", QVariant(args.takeFirst()));

    for(int i = 0; i < args.count(); ++i){
        //  if element 0 matches a switch...
        if(args.at(i) == "-x" || args.at(i) == "--exec"){
            _arguments.insert("exec", QVariant(args.at(i+1))); // do something to element 1
        }else if(args.at(i) == "-c" || args.at(i) == "--config"){
            _arguments.insert("config", QVariant(args.at(i+1)));
        }else if(args.at(i) == "-s" || args.at(i) == "--style"){
            _arguments.insert("style", QVariant(args.at(i+1)));
        }else if(args.at(i) == "-R" || args.at(i) == "--resources"){
            _arguments.insert("resources", QVariant(args.at(i+1)));
        }else if(args.at(i) == "-P" || args.at(i) == "--prefix"){
            _arguments.insert("prefix", QVariant(args.at(i+1)));
        }else if(args.at(i) == "--debug-style"){
            _arguments.insert("debug-style", QVariant(args.at(i+1)));
        }else if(args.at(i) == "-V" || args.at(i) == "--verbosity"){
            _arguments.insert("log-verbosity", QVariant(args.at(i+1)));
        }else if(args.at(i) == "-q" || args.at(i) == "--quiet"){
            _arguments.insert("log-verbosity", QVariant(0));
        }

        //  remove the command
        args.removeFirst();
    }
}

/*!
  Loads and applies a Qt Stylesheet (qss) from a file, either specified on the
  command line or from default locations.

  \todo add default system locations as places to search (home folders,
  system config folders, etc.)
*/
void Zee::reloadStyleSheet()
{
    //	set stylesheet
    QFile qss;

    if(hasArg("style"))
        qss.setFileName(arg("style").toString());
    else if(arg("program").toString() != ZEE_PROGNAME &&
            QFile::exists(arg("program").toString()+".qss"))
        qss.setFileName(arg("program").toString()+".qss");
    else if(QFile::exists(ZUI_DEFAULT_QSS_NAME))
        qss.setFileName(ZUI_DEFAULT_QSS_NAME);
    else
        qss.setFileName(QString(ZEE_CFG_KEY)+":"+QString(ZUI_DEFAULT_QSS_NAME));

    if(qss.open(QIODevice::ReadOnly))
    {
        QTextStream style(&qss);
        setStyleSheet(style.readAll());
        qss.close();
        z_log_debug("Zee: Loaded stylesheet '"+qss.fileName()+"'");
    }else{
        z_log_error("Zee: Unable to locate stylesheet '"+qss.fileName()+"'");
    }

    emit styleReloaded();
}


void Zee::parseUI()
{
    QFile zui;

    //load resources
    if(arg("program").toString() != ZEE_PROGNAME &&
             QFile::exists(arg("program").toString()+".rcc"))
        QResource::registerResource(arg("program").toString()+".rcc");
    else if(QFile::exists(ZUI_DEFAULT_RCC_NAME))
        QResource::registerResource(ZUI_DEFAULT_RCC_NAME);
    else
        QResource::registerResource(QString(ZEE_CFG_KEY)+":"+ZUI_DEFAULT_RCC_NAME);

    if(hasArg("resources")){
        QStringList clres = arg("resources").toString().split(",");
        foreach(QString clr, clres)
            QResource::registerResource(clr);
    }

    //if specified on command line, try that
    if(hasArg("config"))
        zui.setFileName(arg("config").toString());
    else if(arg("program").toString() != ZEE_PROGNAME &&
            QFile::exists(arg("program").toString()+".xml"))
        zui.setFileName(arg("program").toString()+".xml");
    else if(QFile::exists(ZUI_DEFAULT_FILE_NAME))
        zui.setFileName(ZUI_DEFAULT_FILE_NAME);
    else
        zui.setFileName(QString(ZEE_CFG_KEY)+":"+QString(ZUI_DEFAULT_FILE_NAME));

    if(zui.exists()){
        QDomDocument zuiDef("zui");
        QString zDocErr;
        int zDocErrLine;
        int zDocErrCol;
        //make sure we can open the file
        if(!zui.open(QIODevice::ReadOnly)){
            z_log_error("Zee: Failed to open UI definition file '"+zui.fileName()+"'");
            ::exit(ZEE_EXIT_ZUI_DEF_INACCESSIBLE);
        }

        //make sure we can load the data
        if(!zuiDef.setContent(&zui, &zDocErr, &zDocErrLine, &zDocErrCol))
        {
            z_log_error("Zee: ZML Parse Error: line "+STR(zDocErrLine)+", column "+
                        STR(zDocErrCol)+" '"+STR(zDocErr)+"'");
            zui.close();
            ::exit(ZEE_EXIT_INVALID_ZUI_DEF);
        }

        //we're done with this
        zui.close();

        z_log("Zee: Loaded UI definition '"+zui.fileName()+"'");

        QDomElement root = zuiDef.documentElement();
        ZuiParser parser(root);

        return;
    }

    z_log_error("Zee: Unable to locate UI definition file '"+zui.fileName()+"'");
    ::exit(ZEE_EXIT_NO_ZUI_DEF);
}

void Zee::output(QString msg){      z_out(msg);         }
void Zee::log(QString msg){         z_log(msg);         }
void Zee::logWarning(QString msg){  z_log_warn(msg);    }
void Zee::logError(QString msg){    z_log_error(msg);   }
void Zee::logCritical(QString msg){ z_log_crit(msg);    }
void Zee::logDebug(QString msg){    z_log_debug(msg);   }


QVariant Zee::queryProperty(QString zObjPath){
    if(!zObjPath.isEmpty()){
        QObject *obj = zEvent->findObject(zObjPath);

        if(obj){
            QVariant pval = obj->property(CSTR(zObjPath.section(".",-1,-1)));

            if(pval.isValid()){
                emit propertyResponse(pval);
                return pval;
            }else{
                z_log_error("Zee: Property '"+zObjPath.section(".",-1,-1)+"' not found at path '"+zObjPath+"'");
            }
        }else{
            z_log_error("Zee: Object not found at path '"+zObjPath+"'");
        }
    }

    return QVariant();
}


#ifdef Q_WS_X11
bool Zee::x11EventFilter(XEvent *e){
    emit x11EventReceived(e);
    return false;
}
#endif // Q_WS_X11
