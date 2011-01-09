#include "zstyle.h"

ZStyle *ZStyle::_instance = 0;

ZStyle::ZStyle(QString filename, QObject *parent)
    : QObject(parent)
{
    _filename = filename;
    loadFile(filename);
    init();
}

ZStyle::ZStyle(QObject *parent)
    : QObject(parent)
{
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
    zEvent->registerSignal(this, SIGNAL(stylesheetChanged()));

    if(!_basedata.isEmpty())
        parseData();
}


//ZStyleSection &ZStyle::getSection(int id){
//    ZStyleSection &section;

//    if(id >= 0 && id < _sections.count())
//        if(_sections.at(id))
//            section = *_sections.at(id);

//    return section;
//}

void ZStyle::loadFile(QString filename){
    QFile zss(filename);

    if(zss.open(QIODevice::ReadOnly))
    {
        QTextStream data(&zss);
        _basedata = data.readAll();
        zss.close();
        z_log_debug("ZSSParser: Loaded stylesheet '"+zss.fileName()+"'");

        emit stylesheetChanged();
    }else{
        z_log_error("ZSSParser: Unable to locate stylesheet '"+zss.fileName()+"'");
    }
}

void ZStyle::parseData(){
    z_log_debug("ZSSParser: Parsing "+_filename);

//  get everything on one big happy line
    _data = _basedata.replace(QRegExp("[\n\t]")," ");

//  parse the first level of Section{...properties...}
    QRegExp rx("(?:\\s*)([A-Za-z0-9#\\.:-]*)(?:\\s*\\{)([^\\}]*)(?:\\})");
    int i = 0;

    while((i = rx.indexIn(_data,i)) != -1){
        _sections << new ZStyleSection(rx.cap(1), rx.cap(2), this);
        i += rx.matchedLength();
    }

    for(int i = 0; i < _sections.count(); i++){
        _sections[i]->setId(i);
    }
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
