#include "zmaptile.h"

ZMapTile::ZMapTile(int x, int y, QPixmap source){
    setData(_source);
    init(x,y);
}

ZMapTile::ZMapTile(int x, int y, QString source){
    setData(source);
    init(x,y);
}

ZMapTile::ZMapTile(int x, int y){
    init(x,y);
}

void ZMapTile::init(int x, int y){
    _xy.setX(x);
    _xy.setY(y);

    if(_source.isNull()){
        _null = true;
        _source = ZMapTile::emptyTile();
    }else{
        _null = false;
    }
}

void ZMapTile::setData(QPixmap source){
    _source = source;
}

void ZMapTile::setData(QString fileName){
    _source.load(fileName);
}

QPixmap ZMapTile::emptyTile(){
    QPixmap rv;
    rv = QPixmap(TILE_W, TILE_H);
    rv.fill(Qt::transparent);
    QPainter t(&rv);
    QPen tpen(Qt::darkGray);
    tpen.setStyle(Qt::DashLine);
    tpen.setWidth(1);
    t.setPen(tpen);
    t.drawRect(rv.rect());
    t.end();
    return rv;
}

QPoint ZMapTile::coordinates() const{
    return _xy;
}

void ZMapTile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget)
{
    painter->translate(-1*_source.width()/2,
                       -1*_source.height()/2);
    painter->drawPixmap(0,0,
                        _source.width(),_source.height(),
                        _source);
    painter->drawText(2,12,QVariant(pos().x()).toString()+", "+
                      QVariant(pos().y()).toString()+" :: ("+
                      QVariant(_xy.x()).toString()+","+
                      QVariant(_xy.y()).toString()+")");
}

QPainterPath ZMapTile::shape() const{
    QPainterPath p;
    p.addRect(_source.rect());
    return p;
}

QRectF ZMapTile::boundingRect() const{
    return _source.rect();
}

bool ZMapTile::isNull(){
    return _null;
}
