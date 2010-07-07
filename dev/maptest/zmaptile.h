#ifndef ZMAPTILE_H
#define ZMAPTILE_H

#define TILE_W		256
#define	TILE_H		256
#include <QtGui>

class ZMapTile : public QGraphicsItem{

public:
    ZMapTile(int x, int y, QPixmap source);
    ZMapTile(int x, int y, QString source);
    ZMapTile(int x, int y);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    QPainterPath shape() const;
    QRectF boundingRect() const;
    QPoint coordinates() const;
    void setData(QPixmap source);
    void setData(QString fileName);
    bool isNull();
    //void advance(int phase);

public:
    static QPixmap emptyTile();

private:
    void init(int x, int y);

private:
    QPixmap _source;
    QPoint _xy;
    bool _null;
};

#endif // ZMAPTILE_H
