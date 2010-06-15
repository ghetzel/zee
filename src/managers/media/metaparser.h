#ifndef ZMEDIA_META_PARSER_
#define ZMEDIA_META_PARSER_

#include <QtCore>
#include <QHash>

class ZMediaMetaParser : public QObject
{
	Q_OBJECT

	public:
		ZMediaMetaParser(QString _uri);
		virtual QString parseField(QString field) =0;
	protected:
		QString uri;
};

#endif