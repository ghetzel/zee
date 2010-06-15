#include "slippymap.h"

uint qHash(const QPoint& p)
{
    return p.x() * 17 ^ p.y();
}

SlippyMap::SlippyMap(QObject *parent)
    : QObject(parent){
  m_emptyTile = QPixmap(TILE_X_WIDTH, TILE_Y_WIDTH);
  m_emptyTile.fill(Qt::lightGray);

  m_minZoom = MAP_MIN_ZOOM;
  m_maxZoom = MAP_MAX_ZOOM;

  QNetworkDiskCache *cache = new QNetworkDiskCache;
  cache->setCacheDirectory(QDesktopServices::storageLocation
               (QDesktopServices::CacheLocation));
  m_manager.setCache(cache);
  connect(&m_manager, SIGNAL(finished(QNetworkReply*)),
      this, SLOT(handleNetworkData(QNetworkReply*)));
}

bool SlippyMap::setTileBackground(const QPixmap &emptyTile)
{
  if( (emptyTile.width()  == TILE_X_WIDTH) &&
      (emptyTile.height() == TILE_Y_WIDTH)){
    m_emptyTile = emptyTile;
    return true;
  }

  return false;
}

void SlippyMap::setTileSource(const QString &url)
{
//  "http://tile.openstreetmap.org/%1/%2/%3.png"
  m_tileSourceUrl = url;
}

void SlippyMap::setMinimumZoom(int minZoom){
  m_minZoom = minZoom;
}

void SlippyMap::setMaximumZoom(int maxZoom){
  m_maxZoom = maxZoom;
}

void SlippyMap::zoomIn(int byAmount){
  int toAmount = zoom+byAmount;

  if(toAmount <= m_maxZoom)
    zoom = toAmount;
  else
    zoom = m_maxZoom;
  invalidate();
}

void SlippyMap::zoomOut(int byAmount){
  int toAmount = zoom-byAmount;

  if(toAmount >= m_minZoom)
    zoom = toAmount;
  else
    zoom = m_minZoom;
  invalidate();
}

void SlippyMap::zoomTo(int toLevel){
  if(toLevel < m_minZoom)
    zoom = m_minZoom;
  else if(toLevel > m_maxZoom)
    zoom = m_maxZoom;
  else
    zoom = toLevel;

  invalidate();
}

void SlippyMap::invalidate() {
  if (width <= 0 || height <= 0)
    return;

  QPointF ct = SlippyMap::tileForCoordinate(latitude, longitude, zoom);
  qreal tx = ct.x();
  qreal ty = ct.y();

  // top-left corner of the center tile
  int xp = width / 2 - (tx - floor(tx)) * TILE_X_WIDTH;
  int yp = height / 2 - (ty - floor(ty)) * TILE_Y_WIDTH;

  // first tile vertical and horizontal
  int xa = (xp + TILE_X_WIDTH - 1) / TILE_X_WIDTH;
  int ya = (yp + TILE_Y_WIDTH - 1) / TILE_Y_WIDTH;
  int xs = static_cast<int>(tx) - xa;
  int ys = static_cast<int>(ty) - ya;

  // offset for top-left tile
  m_offset = QPoint(xp - xa * TILE_X_WIDTH, yp - ya * TILE_Y_WIDTH);

  // last tile vertical and horizontal
  int xe = static_cast<int>(tx) + (width - xp - 1) / TILE_X_WIDTH;
  int ye = static_cast<int>(ty) + (height - yp - 1) / TILE_Y_WIDTH;

  // build a rect
  m_tilesRect = QRect(xs, ys, xe - xs + 1, ye - ys + 1);

  if (m_url.isEmpty())
    download();

  emit updated(QRect(0, 0, width, height));
}

void SlippyMap::render(QPainter *p, const QRect &rect) {
  for (int x = 0; x <= m_tilesRect.width(); ++x)
    for (int y = 0; y <= m_tilesRect.height(); ++y) {
      QPoint tp(x + m_tilesRect.left(), y + m_tilesRect.top());
      QRect box = tileRect(tp);
      if (rect.intersects(box)) {
        if (m_tilePixmaps.contains(tp))
          p->drawPixmap(box, m_tilePixmaps.value(tp));
        else
          p->drawPixmap(box, m_emptyTile);
      }
    }
}

void SlippyMap::pan(const QPoint &delta) {
  QPointF dx = QPointF(delta) / qreal(TILE_X_WIDTH);
  QPointF center = SlippyMap::tileForCoordinate(latitude, longitude, zoom) - dx;
  latitude = SlippyMap::latitudeFromTile(center.y(), zoom);
  longitude = SlippyMap::longitudeFromTile(center.x(), zoom);
  invalidate();
}


void SlippyMap::handleNetworkData(QNetworkReply *reply) {
  QImage img;
  QPoint tp = reply->request().attribute(QNetworkRequest::User).toPoint();
  QUrl url = reply->url();
  if (!reply->error())
    if (!img.load(reply, 0))
      img = QImage();
  reply->deleteLater();
  m_tilePixmaps[tp] = QPixmap::fromImage(img);
  if (img.isNull())
    m_tilePixmaps[tp] = m_emptyTile;
  emit updated(tileRect(tp));

  // purge unused spaces
  QRect bound = m_tilesRect.adjusted(-2, -2, 2, 2);
  foreach(QPoint tp, m_tilePixmaps.keys())
    if (!bound.contains(tp))
      m_tilePixmaps.remove(tp);

  download();
}

void SlippyMap::download() {
  QPoint grab(0, 0);
  for (int x = 0; x <= m_tilesRect.width(); ++x)
    for (int y = 0; y <= m_tilesRect.height(); ++y) {
      QPoint tp = m_tilesRect.topLeft() + QPoint(x, y);
      if (!m_tilePixmaps.contains(tp)) {
        grab = tp;
        break;
      }
    }
  if (grab == QPoint(0, 0)) {
    m_url = QUrl();
    return;
  }

//tilesource url MUST be set...
  if(!m_tileSourceUrl.isEmpty()){
    QString path = m_tileSourceUrl;
    m_url = QUrl(path.arg(zoom).arg(grab.x()).arg(grab.y()));
    std::cout << "DL :" << m_url.toString().toStdString() << std::endl;
    flush(std::cout);
    QNetworkRequest request;
    request.setUrl(m_url);
    request.setRawHeader("User-Agent", SM_USER_AGENT);
    request.setAttribute(QNetworkRequest::User, QVariant(grab));
    m_manager.get(request);
  }
}


QRect SlippyMap::tileRect(const QPoint &tp) {
  QPoint t = tp - m_tilesRect.topLeft();
  int x = t.x() * TILE_X_WIDTH + m_offset.x();
  int y = t.y() * TILE_Y_WIDTH + m_offset.y();
  return QRect(x, y, TILE_X_WIDTH, TILE_Y_WIDTH);
}

QPointF SlippyMap::tileForCoordinate(qreal lat, qreal lng, int zoom)
{
    qreal zn = static_cast<qreal>(1 << zoom);
    qreal tx = (lng + 180.0) / 360.0;
    qreal ty = (1.0 - log(tan(lat * M_PI / 180.0) +
                          1.0 / cos(lat * M_PI / 180.0)) / M_PI) / 2.0;
    return QPointF(tx * zn, ty * zn);
}

qreal SlippyMap::longitudeFromTile(qreal tx, int zoom)
{
    qreal zn = static_cast<qreal>(1 << zoom);
    qreal lat = tx / zn * 360.0 - 180.0;
    return lat;
}

qreal SlippyMap::latitudeFromTile(qreal ty, int zoom)
{
    qreal zn = static_cast<qreal>(1 << zoom);
    qreal n = M_PI - 2 * M_PI * ty / zn;
    qreal lng = 180.0 / M_PI * atan(0.5 * (exp(n) - exp(-n)));
    return lng;
}

QPixmap SlippyMap::emptyTileItem(){
  return QPixmap(TILE_X_WIDTH, TILE_Y_WIDTH);
}
