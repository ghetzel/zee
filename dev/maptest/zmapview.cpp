#include "zmapview.h"

ZMapView::ZMapView(ZMapScene *scene, QWidget *parent)
    : QGraphicsView(scene,parent)
{
    oX = oY = sX = sY = 0;
    _scene = scene;
    _tileX = OSM_TILE_SX;
    _tileY = OSM_TILE_SY;

    setLayout(new QHBoxLayout);
    layout()->setSpacing(0);
    layout()->setMargin(0);

    redraw();
}

void ZMapView::mousePressEvent(QMouseEvent *e){
//  delta           - the amount the map has moved along x,y during this drag
//  current offset  - the total amount the map has moved along x,y
//  starting offset - the initial point clicked when starting the drag

//  delta coords initialize to current offset coords
    dX = oX;
    dY = oY;
//  starting offset recorded
    sX = e->x();
    sY = e->y();

    qApp->topLevelWidgets().first()->setWindowTitle(QVariant(dX).toString()+
                                                    ", "+QVariant(dY).toString());
    redraw();
}

void ZMapView::mouseMoveEvent(QMouseEvent *e){
//  delta coords updated as (offset coords + current coords) - starting offset
    dX = (oX+e->x())-sX;
    dY = (oY+e->y())-sY;

    redraw();

    qApp->topLevelWidgets().first()->setWindowTitle(QVariant(dX).toString()+", "+QVariant(dY).toString());
}


void ZMapView::mouseReleaseEvent(QMouseEvent *){
    oX = dX;
    oY = dY;

    qApp->topLevelWidgets().first()->setWindowTitle(QVariant(dX).toString()+", "+QVariant(dY).toString()+"*");
    redraw();
}

void ZMapView::updateBounds(){
    if(_scene->sceneRect() != rect()){        
        qDebug() << "UPDATE SCENE RECT";
        _scene->setSceneRect(contentsRect());
        _tilesW = (qCeil(qreal(rect().width())/qreal(TILE_W)));
        _tilesH = (qCeil(qreal(rect().height())/qreal(TILE_H)));
    }

    if( (dX/(_tilesW*(TILE_W/2))) > 0 ){
        _tilesW++;
        addTileColumn(_tileX+_tilesW);
    }

    if( (dY/(_tilesH*(TILE_H/2))) > 0 ){
        _tilesH++;
        addTileRow(_tileY+_tilesH);
    }
}

void ZMapView::updateTilePositions(){
    foreach(ZMapTile *t, _scene->tiles()){
        t->setPos(
            ((t->coordinates().x() - _tileX) * TILE_W)+dX,
            ((t->coordinates().y() - _tileY) * TILE_H)+dY);
    }
}

void ZMapView::redraw(){
    updateBounds();
    updateTilePositions();
    scene()->update();
}

void ZMapView::addTileColumn(int x){
    int yExt = _tileY;

    qDebug() << "ADD COL " << x;
    for(int y = yExt; y < (_tileY+_tilesH); y++)
        _scene->loadTile(x,y,OSM_TILE_ZOOM);
}

void ZMapView::addTileRow(int y){
    int xExt = _tileX;

    qDebug() << "ADD ROW " << y;
    for(int x = xExt; x < (_tileX+_tilesW); x++)
        _scene->loadTile(x,y,OSM_TILE_ZOOM);
}
