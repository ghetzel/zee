#ifndef ZMAPSCENE_H
#define ZMAPSCENE_H

#include <QtGui>
#include <QtNetwork>
#include "zmaptile.h"

class ZMapScene : public QGraphicsScene{
    Q_OBJECT

public:
    typedef QPair<int,int> QIntPair;
    ZMapScene(const QRectF sceneRect=QRectF(), QObject *parent=0);
    void loadTile(uint x, uint y, uint z);
    QList<ZMapTile*> tiles() const;

private slots:
    void handleData(QNetworkReply *);

private:
    QHash<QIntPair, ZMapTile*> _tiles;
    QNetworkAccessManager _net;
    QUrl _uri;
};

#endif // ZMAPSCENE_H
