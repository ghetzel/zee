#include "zstyleparser.h"

ZStyleParser *ZStyleParser::_instance = 0;

ZStyleParser::ZStyleParser(QString filename, QObject *parent)
    : QObject(parent)
{
    _instance = this;
    _filename = filename;
    loadFile(filename);
    init();
}

ZStyleParser::ZStyleParser(QObject *parent)
    : QObject(parent)
{
    _instance = this;
    init();
}

void ZStyleParser::initialize(ZStyleParser *instance){
    if(_instance){
        _instance = instance;
        _instance->init();
    }
}

ZStyleParser *ZStyleParser::instance()
{
//  ZStyleParser MUST have been initialized before being used
    Q_ASSERT(_instance);
    return _instance;
}


void ZStyleParser::init(){
    //zEvent->registerSignal(this, SIGNAL(stylesheetChanged()));

    if(!_basedata.isEmpty())
        parseData();
}

void ZStyleParser::loadFile(QString filename){
    QFile zss(filename);

    if(zss.open(QIODevice::ReadOnly))
    {
        QTextStream data(&zss);
        _basedata = data.readAll();
        zss.close();
        z_log_debug("ZSSParser: Loaded stylesheet '"+zss.fileName()+"'");
    }else{
        z_log_error("ZSSParser: Unable to locate stylesheet '"+zss.fileName()+"'");
    }
}

void ZStyleParser::parseData(){
    z_log_debug("ZSSParser: Parsing "+_filename);

//  get everything on one big happy line
    _data = _basedata.replace(QRegExp("[\n\t\r]")," ");

//  remove comments
    _data = _data.remove(QRegExp("/\\*([^*]|(\\*+([^*/])))*\\*+/"));

//  parse the first level of Section{...properties...}
    QRegExp rx("([^\\{\\}]*)(?:\\{)([^\\}]*)(?:\\})");
    int i = 0;

    while((i = rx.indexIn(_data,i)) != -1){
        _sections << new ZStyleSection(rx.cap(1).trimmed(), rx.cap(2), this);
        i += rx.matchedLength();
    }

    emit stylesheetChanged();
}

QString ZStyleParser::styleSheet(){
    QString rv;

    foreach(ZStyleSection *section, _sections){
        rv += section->toString()+"\n\n";
    }

    return rv;
}

QString ZStyleParser::baseStyleSheet(){
    return _basedata;
}
