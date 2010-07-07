#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(512,512);
}

/*
ZMapView::ZMapView(MapScene *map, QWidget *parent)
    : QGraphicsView(map,parent)
{
    oX = oY = sX = sY = 0;

    _startTX = OSM_TILE_SX;
    _startTY = OSM_TILE_SY;

    _scene = map;

    connect(&_net, SIGNAL(finished(QNetworkReply*)),
	    this, SLOT(handleData(QNetworkReply*)));

    moveTiles();
}

void ZMapView::handleData(QNetworkReply *reply){
    QImage tile;
    QPoint tpt = reply->request().attribute(QNetworkRequest::User).toPoint();
    QIntPair tilepoint = qMakePair(tpt.x(),tpt.y());

    if(!reply->error()){
	if(!tile.load(reply,0))
	    tile = QImage();
	reply->deleteLater();
        _tiles[tilepoint] = new ZMapTile(tpt.x(), tpt.y(), QPixmap::fromImage(tile));
        _scene->addItem(_tiles[tilepoint]);
        qDebug() << "ADD " << tilepoint.first << ", " << tilepoint.second;
        _scene->update();
    }else{
        if(!_tiles.contains(tilepoint))
            _scene->addItem(new ZMapTile(tilepoint.first, tilepoint.second));
    }
}

void ZMapView::moveTiles(){
    updateTiles();

    QIntPair tp;

    for(int i = _startTX; (i-_startTX) < _tilesW; i++){
        for(int j = _startTY; (j-_startTY) < _tilesH; j++){
            tp = qMakePair(i,j);
            _tiles[tp]->setPos(
                ((_tiles[tp]->coordinates().x() - _startTX) * TILE_W)+dX,
                ((_tiles[tp]->coordinates().y() - _startTY) * TILE_H)+dY);
        }
    }
}

void ZMapView::updateBounds(){
    QIntPair tp;

    _scene->setSceneRect(rect());
    _tilesW = (qCeil(qreal(_scene->sceneRect().width())/qreal(TILE_W))+2);
    _tilesH = (qCeil(qreal(_scene->sceneRect().height())/qreal(TILE_H))+2);

    for(int i = _startTX; (i-_startTX) < _tilesW; i++){
        for(int j = _startTY; (j-_startTY) < _tilesH; j++){
            tp = qMakePair(i,j);
            if(!_tiles.contains(tp)){
                _tiles[tp] = new ZMapTile(i,j);
                _scene->addItem(_tiles[tp]);
            }
        }
    }
}

void ZMapView::updateTiles(QPoint){
    updateBounds();
    //QString path = "http://b.tile.openstreetmap.org/%1/%2/%3.png";
    //qDebug() << "Updating...";
    for(int i = _startTX; (i-_startTX) < _tilesW; i++){
        for(int j = _startTY; (j-_startTY) < _tilesH; j++){
            //qDebug() << " (" <<i << "," << j << ")";
	    QPoint cp(i,j);
            QIntPair tp = qMakePair(i,j);
            if(_tiles.contains(tp) && _tiles[tp]->isNull()){
                QString path = "file:///home/ghetzel/projects/gzn/zee/dev/maptest/osm-data/%1/%2/%3.png.tile";
		_uri = QUrl(path.arg(OSM_TILE_ZOOM).arg(i).arg(j));
		QNetworkRequest req;
		req.setUrl(_uri);
		req.setRawHeader("User-Agent", "zee-devel: Geospatial Client Test App 0.05");
		req.setAttribute(QNetworkRequest::User, QVariant(cp));
                qDebug() << "\t GET " << _uri.toString();
		_net.get(req);
            }
	}
    }
}

ZMapView::~ZMapView()
{

}

void ZMapView::mousePressEvent(QMouseEvent *e){


    emit panningStarted();
    _scene->update();
}

void ZMapView::mouseMoveEvent(QMouseEvent *e){
//  delta coords updated as (offset coords + current coords) - starting offset
    dX = (oX+e->x())-sX;
    dY = (oY+e->y())-sY;

    moveTiles();

    _scene->update();
}

void ZMapView::mouseReleaseEvent(QMouseEvent *){
    oX = dX;
    oY = dY;
    qApp->topLevelWidgets().first()->setWindowTitle(QVariant(dX).toString()+", "+QVariant(dY).toString()+"*");

    _scene->update();
    emit panningEnded();
}


    int tx, ty;
    QIntPair tp;
    updateTiles();

    for(int i = _startTX; (i-_startTX) < _tilesW; i++){
        for(int j = _startTY; (j-_startTY) < _tilesH; j++){
	    tp = qMakePair(i,j);
            tx = ((tp.first - _startTX) * 256)+dX;
            ty = ((tp.second - _startTY) * 256)+dY;
            if(_tiles.contains(tp)){
		p->drawPixmap(tx,ty,TILE_W, TILE_H, _tiles.value(tp));
            }else{
                p->drawPixmap(tx,ty,TILE_W, TILE_H, _emptyTile);
                p->drawText(tx+2,ty+12,QVariant(i).toString()+", "+QVariant(j).toString());
            }
	}
    }
    */

//    p->end();
