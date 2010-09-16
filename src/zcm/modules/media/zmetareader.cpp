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

#include "zmetareader.h"

ZMetaReader::ZMetaReader(const ZConfig &el, QObject *parent)
    : QObject(parent),
      ZConfigurable(el,this)
{
    _dataObject = new QObject(this);
    _dataObject->setObjectName("data");

    parse(_config);
    init();
}

void ZMetaReader::init(){
    zEvent->registerSignal(this, SIGNAL(fileChanged(QString)));
    zEvent->registerSignal(this, SIGNAL(dataChanged()));
    zEvent->registerSlot(this, SLOT(setFileName(QString)));
}

void ZMetaReader::parse(const ZConfig &el){
    QDomNodeList children = el.childNodes();
    QDomElement elem;
    QString metatype;

    for(int i = 0; i < children.count(); i++){
	if(!(elem = children.item(i).toElement()).isNull()){
	    if(elem.tagName() == ZCM_METAPROPERTY){
		if(!(metatype = elem.attribute("type")).isEmpty() &&
		   elem.hasAttribute("name") &&
		   elem.hasAttribute("key"))
		{
		    ZMetadata md;
		    md.name = elem.attribute("name");
		    md.type = metatype;
		    md.key = elem.attribute("key");
		    _fields.append(md);

		    //z_log_debug("ZMetaReader: Register metadata parser for type '"+metatype+"'");

		    if(!_parsers.contains(md.type)){
			if(0){
    #ifdef ZMETA_TYPE_AUDIO
			}else if(metatype == ZMETA_TYPE_AUDIO){
			    _parsers.insert(md.type, new ZAudioMetaParser(_source.fileName()));
    #endif
    #ifdef ZMETA_TYPE_IMAGE
			}else if(metatype == ZMETA_TYPE_IMAGE){
    #endif
    #ifdef ZMETA_TYPE_IMAGE_EXIF
			}else if(metatype == ZMETA_TYPE_IMAGE_EXIF){
    #endif
			}
		    }
		}
	    }
	}
    }
}

void ZMetaReader::setFileName(QString location){
    location = QUrl(location).path();

    if(QFile::exists(location)){
	_source.setFileName(location);

	foreach(ZMetaParser *p, _parsers.values())
	    p->setFileName(location);
	emit fileChanged(location);
	fetchMetadata();
    }else{
	z_log_error("ZMetaReader: Cannot find file '"+location+"'");
    }
}

void ZMetaReader::field(QString name){
    QVariant rv;

    if(_dataObject)
        rv = _dataObject->property(CSTR(name));

    emit data(rv);
}

void ZMetaReader::fetchMetadata(){
    ZMetaParser *parser = NULL;

    if(_dataObject){
	foreach(ZMetadata meta, _fields){
	    parser = _parsers.value(meta.type);

	    if(parser){
		_dataObject->setProperty(qstrdup(meta.name.toAscii().data()),
					 parser->field(meta.key));
		if(_dataObject->property(qstrdup(meta.name.toAscii().data())).isValid())
		    z_log_debug("ZMetaReader: Property updated -> "+meta.name+"="+
			    _dataObject->property(qstrdup(meta.name.toAscii().data())).toString());
	    }else{
		z_log_error("ZMetaReader: Parser for type '"+meta.type+"' not found.");
	    }
	}

	emit dataChanged();
    }
}

void ZMetaReader::setAdaptor(ZMetareaderAdaptor *adaptor){
    _adaptor = adaptor;
}
