#include "zstyle.h"

ZStyle *ZStyle::_instance = 0;

ZStyle::ZStyle(QString filename, QObject *parent)
    : QObject(parent)
{
    _instance = this;
    _filename = filename;
    loadFile(filename);
    init();
}

ZStyle::ZStyle(QObject *parent)
    : QObject(parent)
{
    _instance = this;
    init();
}

void ZStyle::initialize(ZStyle *instance){
    if(_instance){
        _instance = instance;
        _instance->init();
    }
}

ZStyle *ZStyle::instance()
{
//  ZStyle MUST have been initialized before being used
    Q_ASSERT(_instance);
    return _instance;
}


void ZStyle::init(){
    //zEvent->registerSignal(this, SIGNAL(stylesheetChanged()));

    if(!_basedata.isEmpty())
        parseData();
}

void ZStyle::loadFile(QString filename){
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

void ZStyle::parseData(){
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

QString ZStyle::styleSheet(){
    QString rv;

    foreach(ZStyleSection *section, _sections){
        rv += section->toString()+"\n\n";
    }

    return rv;
}

QString ZStyle::baseStyleSheet(){
    return _basedata;
}
