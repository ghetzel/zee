#include "zeeindexer.h"

using namespace std;

void ZeeIndexer::run()
{
	reindex();
	cleanup();
}

bool ZeeIndexer::initDb()
{
	zeedb = QSqlDatabase::addDatabase(ZDB_DRIVER);
	zeedb.setHostName(ZDB_HOSTNAME);
	zeedb.setDatabaseName(ZDB_DATABASE);
	zeedb.setUserName(ZDB_USERNAME);
	zeedb.setPassword(ZDB_PASSWORD);
	return zeedb.open();
}

bool ZeeIndexer::reindex()
{
//	let 'em know what we're up to
	emit indexing();

	if(!initDb())
	{
		emit indexFailed();
		return false;
	}

//	load certain static lists of useful information
	loadDataValues();

//	load paths to index
	loadMonitoredPaths();

//	for each monitored path...
	foreach(QString cURI, monitoredPaths)
		indexPath(cURI);

	emit indexingComplete();
	return true;
}


void ZeeIndexer::loadDataValues()
{
	QSqlQuery q(zeedb);
	if(q.exec("SELECT DISTINCT F.extension, M.fieldname, M.id FROM media.metafields M INNER JOIN media.filetypes F ON M.filetype_id = F.id"))
	{
	//	for each result...
		while(q.next())
		{
		//	insert into metafields:	key : id
			metafields.insert(q.value(0).toString(), q.value(1).toString());
			mfieldmap.insert(q.value(1).toString(), q.value(2).toInt());
		}
	}
}

void ZeeIndexer::loadMonitoredPaths()
{
	QSqlQuery q(zeedb);
	if(q.exec("SELECT * FROM media.monitors"))
	{
		int iURI = q.record().indexOf("uri");
	//	for each record
		while(q.next())
		{
			monitoredPaths.append(q.value(iURI).toString());
		}
	}else{
		cout << "SQL: Error:" << q.lastError().databaseText().toStdString() << endl; flush(cout);
	}
}

void ZeeIndexer::cleanup()
{
	QString cn = zeedb.connectionName();
	QSqlDatabase::removeDatabase(cn);
}

bool ZeeIndexer::indexPath(QString uri)
{
	QDir dir(uri);
	QStringList entries;
	QFileInfo *cFile = new QFileInfo(uri);
	QString cPath, cExt;

//	directory must exist and be a directory
	if(dir.exists() && cFile->isDir())
	{
	//	get this directory's entries
		entries = dir.entryList(QDir::AllEntries|QDir::NoDotAndDotDot);
		
	//	for each entry...
		foreach(QString entry, entries)
		{
		//	set path, get info
			cPath = uri+"/"+entry;
			cFile = new QFileInfo(cPath);
			cExt = cFile->suffix().toLower();
		//	directories: recurse to get more
			if(cFile->isDir()){
				cout << "\tDir:" << entry.toStdString() << endl; flush(cout);
				indexPath(cPath);
			}else{
		//	files:	index
			//	only import files for whom we have an extension in the database
				if(metafields.keys().indexOf(cExt) >= 0)
					importItem(cPath, new ZMediaObject(&metafields.values(cExt)));
			}
		}
		return true;
	}

	return false;
}

bool ZeeIndexer::importItem(QString uri, ZMediaObject *metaParser)
{
//	cout << "\tEnter Import item:" << uri.toStdString() << endl; flush(cout);
	QFileInfo cFile(uri);
	QHash<QString,QString> metadata;

//	if file: exists, is a file, and is readable...
	if(cFile.exists() && cFile.isFile() && cFile.isReadable())
	{

		int itemId = 0;
		QSqlQuery q(zeedb);

	//	insert new item if itemId, otherwise update
		q.prepare("SELECT media.SetItem(:uri, :created, :modified)");
		q.bindValue(":uri", uri);
		q.bindValue(":created", cFile.created());
		q.bindValue(":modified", cFile.lastModified());

		if(q.exec())
		{
			q.next();
			itemId = q.value(0).toInt();

		//	get the current file modification info
			q.prepare("SELECT updated_at FROM media.items WHERE id = :item AND updated_at IS NOT NULL");
			q.bindValue(":item", itemId);
			q.exec();

			if(q.next())
			{
				QDateTime fMod = q.value(0).toDateTime();

			//	if the file hasn't changed, dont go any further
				if(cFile.lastModified().toUTC() <= fMod)
				{
					return false;
				}
			}

			try{
			//	get the metadata of the file
				metadata = metaParser->parseMeta(uri);
			}catch(exception& e){
				cout << "**ERROR Parsing " << uri.toStdString() << endl; flush(cout);
				return false;
			}

		//	for each metadata item...
			foreach(QString datum, metadata.keys())
			{
			//	prepare query
				q.prepare("SELECT media.SetMetadata(:item, :metafield, :value)");

			//	bind values
				q.bindValue(":item", itemId);
				q.bindValue(":metafield", mfieldmap.value(datum));
				q.bindValue(":value", metadata.value(datum));
			
			//	execute
				q.exec();
			}
		}else{
			cout << "SQL: Error:" << q.lastError().databaseText().toStdString() << endl; flush(cout);
		}
	}

	return true;
}