#include "zmapscene.h"

ZMapScene::ZMapScene(QRectF sceneRect, QObject *parent)
    : QGraphicsScene(sceneRect, parent){

    setBackgroundBrush(QBrush(Qt::gray));

    connect(&_net, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(handleData(QNetworkReply*)));
}

void ZMapScene::loadTile(uint x, uint y, uint z){
    QString path = "file:///home/ghetzel/projects/gzn/zee/dev/maptest/osm-data/%1/%2/%3.png.tile";
    _uri = QUrl(path.arg(z).arg(x).arg(y));
    QNetworkRequest req;
    req.setUrl(_uri);
    req.setRawHeader("User-Agent", "zee-devel: Geospatial Client Test App 0.05");
    req.setAttribute(QNetworkRequest::User, QVariant(QPoint(x,y)));
    qDebug() << "\t GET " << _uri.toString();
    _net.get(req);
}

void ZMapScene::handleData(QNetworkReply *reply){
    QImage tile;
    QPoint tp = reply->request().attribute(QNetworkRequest::User).toPoint();
    QIntPair tilepoint = qMakePair(tp.x(),tp.y());

    if(!reply->error()){
        if(!tile.load(reply,0))
            tile = QImage();
        reply->deleteLater();
        _tiles[tilepoint] = new ZMapTile(tp.x(), tp.y(), QPixmap::fromImage(tile));
        addItem(_tiles[tilepoint]);
        qDebug() << "\tADD " << tilepoint.first << ", " << tilepoint.second;
    }else{
        if(!_tiles.contains(tilepoint)){
            _tiles[tilepoint] = new ZMapTile(tp.x(), tp.y());
            addItem(_tiles[tilepoint]);
            //qDebug() << "\tADD EMPTY " << tilepoint.first << ", " << tilepoint.second;
        }
    }

    update();
}

QList<ZMapTile*> ZMapScene::tiles() const{
    return _tiles.values();
}
