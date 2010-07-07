#ifndef ZMAPVIEW_H
#define ZMAPVIEW_H

#define OSM_TILE_ZOOM	17
#define OSM_TILE_SX	38509
#define OSM_TILE_SY	49308

#include <QtGui>
#include "zmapscene.h"

class ZMapView : public QGraphicsView
{
    Q_OBJECT
public:
    ZMapView(ZMapScene *scene, QWidget *parent=0);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private:
    void updateBounds();
    void updateTilePositions();
    void redraw();
    void addTileColumn(int x);
    void addTileRow(int y);    

private:
    ZMapScene *_scene;
    qint64 oX, oY;
    qint64 sX, sY;
    qint64 dX, dY;
    uint _tileX;
    uint _tileY;
    uint _tilesW;
    uint _tilesH;

};

#endif // ZMAPVIEW_H
