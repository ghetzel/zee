#include "mp3parser.h"

ZMp3Parser::ZMp3Parser(QString _uri) : ZMediaMetaParser(_uri)
{
//	link to the URI, gathering ID3v1/2 tags
	file = new TagLib::FileRef(_uri.toUtf8().data());
}

QString ZMp3Parser::parseField(QString field)
{
//	cout << "\t\tParse field: " << field.toStdString() << endl; flush(cout);
	QString qData;
	TagLib::String data_s = "";
	int data_i = 0;


	if(field == "TITLE"){
		data_s = file->tag()->title();
	}else if(field == "ARTIST"){
		data_s = file->tag()->artist();
	}else if(field == "ALBUM"){
		data_s = file->tag()->album();
	}else if(field == "TRACK"){
		data_i = static_cast<int>(file->tag()->track());
	}else if(field == "GENRE"){
		data_s = file->tag()->genre();
	}else if(field == "YEAR"){
		data_i = static_cast<int>(file->tag()->year());
	}else if(field == "COMMENT"){
		data_s = file->tag()->comment();
	}else if(field == "LENGTH"){
		data_i = static_cast<int>(file->audioProperties()->length());
	}else if(field == "BITRATE"){
		data_i = static_cast<int>(file->audioProperties()->bitrate());
	}else if(field == "SAMPLERATE"){
		data_i = static_cast<int>(file->audioProperties()->sampleRate());
	}else if(field == "CHANNELS"){
		data_i = static_cast<int>(file->audioProperties()->channels());
	}

	if(data_i != 0)
		qData = data_i;
	else
		qData = data_s.toCString(true);

	return qData;
}