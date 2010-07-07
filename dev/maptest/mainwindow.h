#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define OSM_TILE_TW	3
#define OSM_TILE_TH	3

#include <QtCore>
#include <QtGui>
#include <QtNetwork>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
};


/*
class ZMapView : public QGraphicsView
{
    Q_OBJECT

public:
    typedef QPair<int,int> QIntPair;
    ZMapView(MapScene *map, QWidget *parent = 0);
    ~ZMapView();
    void moveTiles();

public slots:
    void updateTiles(QPoint center=QPoint(0,0));

private slots:
    void handleData(QNetworkReply *);
    void updateBounds();

signals:
    void panningStarted();
    void panningEnded();

private:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private:
    qint64 oX, oY;
    qint64 sX, sY;
    qint64 dX, dY;
    int _tilesW, _tilesH;
    int _startTX, _startTY;
    bool _dragging;
    QNetworkAccessManager _net;
    QUrl _uri;
    QHash<QIntPair, ZMapTile*> _tiles;
    QPoint _center;
    QGraphicsScene *_scene;
};
*/

#endif // MAINWINDOW_H
