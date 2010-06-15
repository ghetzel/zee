#ifndef ZMEDIA_OBJECT_
#define ZMEDIA_OBJECT_

#include <QtCore>
#include <managers/media/metaparsers/mp3parser.h>

class ZMediaObject : public QObject
{
	Q_OBJECT
	public:
		ZMediaObject(QList<QString> *_metafields);
		virtual QHash<QString,QString> parseMeta(QString uri);

	private:
		QString uri;
		QList<QString> metafields;
};

#endif