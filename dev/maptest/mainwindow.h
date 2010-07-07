#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define TILE_W		256
#define	TILE_H		256
#define OSM_TILE_ZOOM	16
#define OSM_TILE_SX	19292
#define OSM_TILE_SY	24771
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

class MapWidget : public QWidget
{
    Q_OBJECT

public:
    typedef QPair<int,int> QIntPair;
    MapWidget(QWidget *parent = 0);
    ~MapWidget();
    void paintEvent(QPaintEvent *);

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
    QHash<QIntPair, QPixmap> _tiles;
    QPoint _center;
    QPixmap _emptyTile;
};

#endif // MAINWINDOW_H
