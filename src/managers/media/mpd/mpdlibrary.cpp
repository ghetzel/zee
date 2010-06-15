#include "mpdlibrary.h"

MpdLibrary::MpdLibrary(MpdObj *_server)
{
	server = _server;
}

QList<QHash<QString,QVariant> > MpdLibrary::query(QString search)
{
}

QList<QHash<QString,QVariant> > MpdLibrary::getByMetafield(QString metafield)
{
	MpdData *q = NULL;
	QList<QHash<QString,QVariant> > resultset;
	QHash<QString,QVariant> resRow;

	if(metafield.toUpper() == "ARTIST"){
		q = mpd_database_get_artists(server);
	}else if(metafield.toUpper() == "ALBUM"){
		q = mpd_database_get_albums(server, NULL);
	}else if(metafield.toUpper() == "TITLE"){
		q = mpd_database_get_complete(server);
	}

	for(MpdData *data = q; data != NULL; data = mpd_data_get_next(data))
	{
		if(data->type == MPD_DATA_TYPE_SONG)
		{
			resRow.insert("id", QVariant(data->song->id));
			resRow.insert("value", QVariant(data->song->title));
		}else if(data->type == MPD_DATA_TYPE_TAG){
			resRow.insert("id", QVariant(NULL));
			resRow.insert("value", QVariant(data->tag));
		}

		resultset.append(resRow);
	}

	return resultset;
}

ZMediaIndexer *MpdLibrary::indexer()
{
	return NULL;
}