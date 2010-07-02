#include "zfolderview.h"

ZFolderView::ZFolderView(const ZConfig &el, QWidget *parent)
  : ZFileBrowser(el,parent){
  init();
}

ZFolderView::ZFolderView(QDir initDirectory, const ZConfig &el, QWidget *parent)
  : ZFileBrowser(el,parent){
  init();
  cd(initDirectory);
}

ZFolderView::ZFolderView(QString initDirectory, const ZConfig &el, QWidget *parent)
  : ZFileBrowser(el,parent){
  init();
  cd(initDirectory);
}

void ZFolderView::init(){
//  setWrapping(true);
//  setWordWrap(true);
//  setSelectionRectVisible(true);
//  setSelectionMode(QAbstractItemView::ExtendedSelection);
}
