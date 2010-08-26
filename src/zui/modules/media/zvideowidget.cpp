#include "zvideowidget.h"

ZVideoWidget::ZVideoWidget(const ZConfig &el, QWidget *parent)
    : ZWidget<VideoPlayer>(el,this,parent)
{
    init();
}

void ZVideoWidget::init(){
    zEvent->registerSignal(this,SIGNAL(sourceChanged(QString)));
    zEvent->registerSlot(this, SLOT(play()));
    zEvent->registerSlot(this, SLOT(pause()));
    zEvent->registerSlot(this, SLOT(stop()));
    zEvent->registerSlot(this, SLOT(load(QString)));
    parse(_config);
}

void ZVideoWidget::parse(const ZConfig&){

}

void ZVideoWidget::load(QString location){
    _source = new MediaSource(location);
    VideoPlayer::load(*_source);
    emit sourceChanged(_source->fileName());
    z_log_debug("ZVideoWidget: "+STR(totalTime()));
}
