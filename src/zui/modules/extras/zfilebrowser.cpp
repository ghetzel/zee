#include "zfilebrowser.h"


ZFileBrowser::ZFileBrowser(const ZConfig &el, QWidget *parent)
    : ZListWidget(el,parent){
    init();
    cd(ZUI_FLIST_DEFAULT_DIR);
}

ZFileBrowser::ZFileBrowser(QDir initDirectory, const ZConfig &el, QWidget *parent)
    : ZListWidget(el,parent){
    init();
    cd(initDirectory);
}

ZFileBrowser::ZFileBrowser(QString initDirectory, const ZConfig &el, QWidget *parent)
    : ZListWidget(el,parent){
    init();
    cd(initDirectory);
}

void ZFileBrowser::parse(const ZConfig &el){
    if(el.hasAttribute("uri"))
	cd(el.attribute("uri"));
}

void ZFileBrowser::init(){
    pwd = new QFileSystemModel(this);
    setModel(pwd);

    parse(_config);

    zEvent->registerSignal(this,SIGNAL(activated(QStringList)));
    zEvent->registerSignal(this,SIGNAL(activated(QString)));
    zEvent->registerSignal(this,SIGNAL(directoryChanged(QString)));
    zEvent->registerSlot(this,SLOT(cd(QString)));
    zEvent->registerSlot(this,SLOT(cdUp()));

    connect(this, SIGNAL(doubleClicked(QModelIndex)),
	    this, SLOT(cd(QModelIndex)));
    connect(this, SIGNAL(activated(QModelIndex)),
	    this, SLOT(_activated(QModelIndex)));
}


void ZFileBrowser::_activated(const QModelIndex &index){
    QStringList fps;
    z_log("ZFileBrowser: Activated: " + STR(selectedIndexes().count()));
    foreach(QModelIndex i, selectedIndexes()){
        fps << i.data(QFileSystemModel::FilePathRole).toString();
    }
    emit activated(fps);
}

bool ZFileBrowser::cd(QModelIndex itemIndex){
    if(pwd)
	if(pwd->isDir(itemIndex))
	    return cd(itemIndex.data(QFileSystemModel::FilePathRole).toString());
        else
            _activated(itemIndex);
}

bool ZFileBrowser::cd(QDir directory){
    return cd(directory.dirName());
}

bool ZFileBrowser::cd(QString directory){
    if(pwd)
	setRootIndex(pwd->setRootPath(directory));
    return true;
}


void ZFileBrowser::keyPressEvent(QKeyEvent *event){

    if(event->key() == Qt::Key_Return){
	if(!selectedIndexes().empty())
	    cd(selectedIndexes().first());
    }else if(event->key() == Qt::Key_Up &&
	     event->modifiers() == Qt::AltModifier){
	cdUp();
    }else{
	QListView::keyPressEvent(event);
    }
}

bool ZFileBrowser::cdUp(){
    QDir du = pwd->rootDirectory();
    du.cdUp();
    setRootIndex(pwd->setRootPath(du.path()));
    return true;
}
