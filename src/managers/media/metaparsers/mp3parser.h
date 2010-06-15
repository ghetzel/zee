#ifndef ZMEDIA_METAPARSER_MP3_
#define ZMEDIA_METAPARSER_MP3_

#include <iostream>
#include <fileref.h>
#include <tag.h>
#include <QVariant>
#include <QString>
#include <managers/media/metaparser.h>

using namespace std;

class ZMp3Parser : public ZMediaMetaParser
{
	public:
		ZMp3Parser(QString _uri);
		QString parseField(QString field);
		
	private:
		TagLib::FileRef *file;
};

#endif