#include "zseekbar.h"

ZSeekbar::ZSeekbar(const ZConfig &el, QWidget *parent)
    : ZWidget<QWidget>(el,this,parent)
{
    init();
}

void ZSeekbar::init(){
    parse(_config);
}

void ZSeekbar::parse(const ZConfig &el){

}

void ZSeekbar::paintEvent(QPaintEvent *e){
    QPainter *p = new QPainter(this);


}
