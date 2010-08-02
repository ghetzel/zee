#include "zhtmlfolderview.h"

ZHTMLFolderView::ZHTMLFolderView(const ZConfig &el, QWidget *parent)
    : ZListWidget(el,parent)
{
    parse(_config);
    init();
}

void ZHTMLFolderView::parse(const ZConfig &el){
    if(el.hasAttribute("uri")){
        _model = new ZHTMLListModel(QUrl::fromUserInput(el.attribute("uri")),
                                    this);
        setModel(_model);
    }
}

void ZHTMLFolderView::init(){
    zEvent->registerSlot(this, SLOT(setUrl(QString)));
}

void ZHTMLFolderView::setUrl(QString location){
    if(_model){
        _model->setBaseUrl(QUrl::fromUserInput(location));
    }
}
