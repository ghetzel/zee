#ifndef SLIPPYMAP_H
#define SLIPPYMAP_H

#include <iostream>
#include <math.h>
#include <QtCore>
#include <QtGui>
#include <QtNetwork>

#define MAP_MIN_ZOOM    1
#define MAP_MAX_ZOOM    17
#define TILE_X_WIDTH    256
#define TILE_Y_WIDTH    256
#define SM_USER_AGENT   "Nokia (Qt) Graphics Dojo 1.0"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


class SlippyMap : public QObject
{
    Q_OBJECT

public:
    int width;
    int height;
    int zoom;
    qreal latitude;
    qreal longitude;

    SlippyMap(QObject *parent = 0);
    void invalidate();
    void render(QPainter *p, const QRect &rect);
    void pan(const QPoint &delta);

    bool setTileBackground(const QPixmap &emptyTile);
    void setTileSource(const QString &url);
    void setMinimumZoom(int minZoom = MAP_MIN_ZOOM);
    void setMaximumZoom(int maxZoom = MAP_MAX_ZOOM);

    static QPointF tileForCoordinate(qreal lat, qreal lng, int zoom);
    static qreal longitudeFromTile(qreal tx, int zoom);
    static qreal latitudeFromTile(qreal ty, int zoom);
    static QPixmap emptyTileItem();

public slots:
    void zoomIn(int byAmount = 1);
    void zoomOut(int byAmount = 1);
    void zoomTo(int toLevel);

private slots:
    void handleNetworkData(QNetworkReply *reply);
    void download();

signals:
    void updated(const QRect &rect);

protected:
    QRect tileRect(const QPoint &tp);

private:
    int m_minZoom, m_maxZoom;
    QPoint m_offset;
    QRect m_tilesRect;
    QPixmap m_emptyTile;
    QHash<QPoint, QPixmap> m_tilePixmaps;
    QNetworkAccessManager m_manager;
    QString m_tileSourceUrl;
    QUrl m_url;
};

#endif // SLIPPYMAP_H
