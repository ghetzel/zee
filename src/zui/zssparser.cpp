#include "zssparser.h"

ZSSParser::ZSSParser(QString filename, QObject *parent)
    : QObject(parent)
{
    _filename = filename;
    loadFile(filename);
    init();
}

ZSSParser::ZSSParser(QObject *parent)
    : QObject(parent)
{
    init();
}


void ZSSParser::init(){
    if(!_basedata.isEmpty())
        parseData();
}

void ZSSParser::loadFile(QString filename){
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

void ZSSParser::parseData(){
    z_log_debug("ZSSParser: Parsing "+_filename);

//  get everything on one big happy line
    _data = _basedata.replace(QRegExp("[\n\t]")," ");

//  parse the first level of Section{...properties...}
    QRegExp rx("(?:\\s*)([A-Za-z0-9#\\.:-]*)(?:\\s*\\{)([^\\}]*)(?:\\})");
    int i = 0;

    while((i = rx.indexIn(_data,i)) != -1){
        int j = 0;

    //  parse property: value;
        QRegExp drx("([A-Za-z0-9-]*)(?:\\s*:\\s*)([^;]*)(?:\\s*;\\s*)");
        z_log_debug("ZSSParser:  "+rx.cap(1)+" {");

        while((j = drx.indexIn(rx.cap(2),j)) != -1){
            z_log_debug("ZSSParser:       "+ZString(drx.cap(1)).lpad(16)+"    "+ZString(drx.cap(2)));

            j += drx.matchedLength();
        }

        z_log_debug("ZSSParser:  }");

        i += rx.matchedLength();
    }

}
