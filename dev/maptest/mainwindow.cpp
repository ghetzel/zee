#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(512,512);
}

MapWidget::MapWidget(QWidget *parent)
    : QWidget(parent)
{
    cX = rect().width()/2;
    cY = rect().height()/2;

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
//    qDebug() << "Data Inbound";
    QImage tile;
    QPoint tpt = reply->request().attribute(QNetworkRequest::User).toPoint();
    QIntPair tilepoint = qMakePair(tpt.x(),tpt.y());

    if(!reply->error()){
	if(!tile.load(reply,0))
	    tile = QImage();
	reply->deleteLater();
	_tiles[tilepoint] = QPixmap::fromImage(tile);
	repaint(rect());
    }else{
//	qDebug() << "Error: " << reply->errorString();
    }
}

void MapWidget::updateBounds(){
    _tilesW = qCeil(qreal(rect().width())/qreal(TILE_W))+2;
    _tilesH = qCeil(qreal(rect().height())/qreal(TILE_H))+2;
}

void MapWidget::updateTiles(QPoint center){
    updateBounds();
    //QString path = "http://b.tile.openstreetmap.org/%1/%2/%3.png";
    //qDebug() << "Updating...";
    for(int i = OSM_TILE_SX; (i-OSM_TILE_SX) < _tilesW; i++){
	//qDebug() << "X-coord: " << i;
	for(int j = OSM_TILE_SY; (j-OSM_TILE_SY) < _tilesH; j++){
	    //qDebug() << "\tY-coord: " << j;
	    QPoint cp(i,j);
	    if(!_tiles.contains(qMakePair(cp.x(),cp.y()))){
		QString path = "file:///home/ghetzel/projects/zee/dev/osm/%1/%2/%3.png";
		_uri = QUrl(path.arg(OSM_TILE_ZOOM).arg(i).arg(j));
		QNetworkRequest req;
		req.setUrl(_uri);
		req.setRawHeader("User-Agent", "zee-devel: Geospatial Client Test App 0.05");
		req.setAttribute(QNetworkRequest::User, QVariant(cp));
		//qDebug() << "Requesting " << _uri.toString();
		_net.get(req);
	    }
	}
    }
}

MapWidget::~MapWidget()
{

}

void MapWidget::mousePressEvent(QMouseEvent *e){
    //cX += ((-1*cX)+e->x());
    //cY += ((-1*cY)+e->y());
    qDebug() << "PRESS "<<cX<<","<<cY;
}

void MapWidget::mouseMoveEvent(QMouseEvent *e){
    dX = (-1*cX)+e->x();
    dY = (-1*cY)+e->y();
    repaint(rect());
    qDebug() << "MOVE "<<dX<<","<<dY;
}

void MapWidget::mouseReleaseEvent(QMouseEvent *e){
    cX += dX;
    cY += dY;
    qDebug() << "RELES "<<cX<<","<<cY;
}

void MapWidget::paintEvent(QPaintEvent *e){
    int tx, ty;
    QPainter *p = new QPainter(this);
    QIntPair tp;
    updateTiles();

    for(int i = OSM_TILE_SX; (i-OSM_TILE_SX) < _tilesW; i++){
	for(int j = OSM_TILE_SY; (j-OSM_TILE_SY) < _tilesH; j++){
	    tp = qMakePair(i,j);
	    tx = ((tp.first - OSM_TILE_SX) * 256)+dX;
	    ty = ((tp.second - OSM_TILE_SY) * 256)+dY;
	    if(_tiles.contains(tp))
		p->drawPixmap(tx,ty,TILE_W, TILE_H, _tiles.value(tp));
	    else
		p->drawPixmap(tx,ty,TILE_W, TILE_H, _emptyTile);
	}
    }

    p->end();
}
