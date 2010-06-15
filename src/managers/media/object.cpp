#include "object.h"

using namespace std;

ZMediaObject::ZMediaObject(QList<QString> *_metafields = NULL)
{
	if(_metafields)
		metafields = *_metafields;
}

QHash<QString,QString> ZMediaObject::parseMeta(QString uri)
{
//	cout << "\tMetaParse: " << uri.toStdString() << endl; flush(cout);

	QHash<QString,QString> metadata;
	QString pField;
	QFileInfo cFile(uri);
	QString cExt = cFile.suffix();
	ZMediaMetaParser *parser = NULL;

	if(cExt == "mp3"){
		parser = new ZMp3Parser(uri);
	}else if(cExt == "ogg"){

	}

	if(parser)
	{
	//	for each field...
		for(int i = 0; i < metafields.count(); i++)
		{
			if((pField = parser->parseField(metafields.value(i))) != NULL )
				metadata.insert(metafields.value(i), pField);
		}
	}

	return metadata;
}