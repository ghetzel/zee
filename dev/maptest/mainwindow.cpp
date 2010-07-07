#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(512,512);
}

MapWidget::MapWidget(QWidget *parent)
    : QWidget(parent)
{
    oX = oY = sX = sY = 0;

    _startTX = OSM_TILE_SX;
    _startTY = OSM_TILE_SY;


    _emptyTile = QPixmap(TILE_W, TILE_H);
    _emptyTile.fill(Qt::transparent);

    QPainter t(&_emptyTile);
    QPen tpen(Qt::darkGray);
    tpen.setStyle(Qt::DashLine);
    tpen.setWidth(1);
    t.setPen(tpen);
    t.drawRect(_emptyTile.rect());
    t.end();

    connect(&_net, SIGNAL(finished(QNetworkReply*)),
	    this, SLOT(handleData(QNetworkReply*)));
    updateTiles();
}

void MapWidget::handleData(QNetworkReply *reply){
    QImage tile;
    QPoint tpt = reply->request().attribute(QNetworkRequest::User).toPoint();
    QIntPair tilepoint = qMakePair(tpt.x(),tpt.y());

    if(!reply->error()){
	if(!tile.load(reply,0))
	    tile = QImage();
	reply->deleteLater();
	_tiles[tilepoint] = QPixmap::fromImage(tile);
        qDebug() << "ADD " << tilepoint.first << ", " << tilepoint.second;
        repaint(rect());
    }else{
//	qDebug() << "Error: " << reply->errorString();
    }
}

void MapWidget::updateBounds(){
    _tilesW = (qCeil(qreal(rect().width())/qreal(TILE_W))+2);
    _tilesH = (qCeil(qreal(rect().height())/qreal(TILE_H))+2);
}

void MapWidget::updateTiles(QPoint){
    updateBounds();
    //QString path = "http://b.tile.openstreetmap.org/%1/%2/%3.png";
    //qDebug() << "Updating...";
    for(int i = _startTX; (i-_startTX) < _tilesW; i++){
        for(int j = _startTY; (j-_startTY) < _tilesH; j++){
            //qDebug() << " (" <<i << "," << j << ")";
	    QPoint cp(i,j);
            if(!_tiles.contains(qMakePair(i,j))){
                QString path = "file:///home/ghetzel/projects/gzn/zee/dev/osm/%1/%2/%3.png";
		_uri = QUrl(path.arg(OSM_TILE_ZOOM).arg(i).arg(j));
		QNetworkRequest req;
		req.setUrl(_uri);
		req.setRawHeader("User-Agent", "zee-devel: Geospatial Client Test App 0.05");
		req.setAttribute(QNetworkRequest::User, QVariant(cp));
                //qDebug() << "\t GET " << _uri.toString();
		_net.get(req);
	    }
	}
    }
}

MapWidget::~MapWidget()
{

}

void MapWidget::mousePressEvent(QMouseEvent *e){
//  delta coords initialize to current offset coords
    dX = oX;
    dY = oY;
//  starting offset recorded
    sX = e->x();
    sY = e->y();

    emit panningStarted();
    repaint(rect());
}

void MapWidget::mouseMoveEvent(QMouseEvent *e){
//  delta coords updated as (offset coords + current coords) - starting offset
    dX = (oX+e->x())-sX;
    dY = (oY+e->y())-sY;

    qApp->topLevelWidgets().first()->setWindowTitle(QVariant(dX).toString()+", "+QVariant(dY).toString());
    repaint(rect());
}

void MapWidget::mouseReleaseEvent(QMouseEvent *){
    oX = dX;
    oY = dY;
    qApp->topLevelWidgets().first()->setWindowTitle(QVariant(dX).toString()+", "+QVariant(dY).toString()+"*");

    repaint(rect());
    emit panningEnded();
}

void MapWidget::paintEvent(QPaintEvent *){
    int tx, ty;
    QPainter *p = new QPainter(this);
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

    p->end();
}
