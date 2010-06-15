#include "zmapwidget.h"

ZMapWidget::ZMapWidget(QWidget *parent)
 : QWidget(parent)
    , pressed(false)
    , snapped(false)
    , zoomed(false)
    , invert(false) {
  m_normalMap = new SlippyMap(this);


  m_normalMap->setTileSource("http://tile.openstreetmap.org/%1/%2/%3.png");
  //m_normalMap->setTileSource("http://mt2.google.com/mt?n=404&x=%2,y=%3&zoom=%1&t=m");
  setCenter(40.058158, -74.134758);


  QPixmap emptyTile = SlippyMap::emptyTileItem();
  emptyTile.fill(QColor(0,0,0,128));
  m_normalMap->setTileBackground(emptyTile);

  //m_largeMap = new SlippyMap(this);
  connect(m_normalMap, SIGNAL(updated(QRect)), SLOT(updateMap(QRect)));
  //connect(m_largeMap, SIGNAL(updated(QRect)), SLOT(update()));
}

QSize ZMapWidget::sizeHint(){
    return QSize(ZMAP_DEFAULT_WIDTH, ZMAP_DEFAULT_HEIGHT);
}

void ZMapWidget::setCenter(qreal lat, qreal lng) {
  m_normalMap->latitude = lat;
  m_normalMap->longitude = lng;
  m_normalMap->invalidate();
  //m_largeMap->invalidate();
}

void ZMapWidget::setCenter(QPointF &point){
  setCenter(point.x(), point.y());
}


void ZMapWidget::toggleNightMode() {
  invert = !invert;
  update();
}


void ZMapWidget::updateMap(const QRect &r) {
  update(r);
}

void ZMapWidget::activateZoom() {
  zoomed = true;
  tapTimer.stop();
//  m_largeMap->zoom = m_normalMap->zoom + 1;
//  m_largeMap->width = m_normalMap->width * 2;
//  m_largeMap->height = m_normalMap->height * 2;
//  m_largeMap->latitude = m_normalMap->latitude;
//  m_largeMap->longitude = m_normalMap->longitude;
//  m_largeMap->invalidate();
  update();
}

void ZMapWidget::resizeEvent(QResizeEvent *) {
  m_normalMap->width = width();
  m_normalMap->height = height();
  m_normalMap->invalidate();
//  m_largeMap->width = m_normalMap->width * 2;
//  m_largeMap->height = m_normalMap->height * 2;
//  m_largeMap->invalidate();
}

void ZMapWidget::paintEvent(QPaintEvent *event) {
  QPainter p;
  p.begin(this);
  m_normalMap->render(&p, event->rect());
  p.setPen(Qt::black);
#if defined(Q_OS_SYMBIAN)
  QFont font = p.font();
  font.setPixelSize(13);
  p.setFont(font);
#endif
  //p.drawText(rect(),  Qt::AlignBottom | Qt::TextWordWrap,
  //       "Map data CCBYSA 2009 OpenStreetMap.org contributors");
  p.end();

/*
  if (zoomed) {
    int dim = qMin(width(), height());
    int magnifierSize = qMin(MAX_MAGNIFIER, dim * 2 / 3);
    int radius = magnifierSize / 2;
    int ring = radius - 15;
    QSize box = QSize(magnifierSize, magnifierSize);

    // reupdate our mask
    if (maskPixmap.size() != box) {
      maskPixmap = QPixmap(box);
      maskPixmap.fill(Qt::transparent);

      QRadialGradient g;
      g.setCenter(radius, radius);
      g.setFocalPoint(radius, radius);
      g.setRadius(radius);
      g.setColorAt(1.0, QColor(255, 255, 255, 0));
      g.setColorAt(0.5, QColor(128, 128, 128, 255));

      QPainter mask(&maskPixmap);
      mask.setRenderHint(QPainter::Antialiasing);
      mask.setCompositionMode(QPainter::CompositionMode_Source);
      mask.setBrush(g);
      mask.setPen(Qt::NoPen);
      mask.drawRect(maskPixmap.rect());
      mask.setBrush(QColor(Qt::transparent));
      mask.drawEllipse(g.center(), ring, ring);
      mask.end();
    }

    QPoint center = dragPos - QPoint(0, radius);
    center = center + QPoint(0, radius / 2);
    QPoint corner = center - QPoint(radius, radius);

    QPoint xy = center * 2 - QPoint(radius, radius);

    // only set the dimension to the magnified portion
    if (zoomPixmap.size() != box) {
      zoomPixmap = QPixmap(box);
      zoomPixmap.fill(Qt::lightGray);
    }
    if (true) {
      QPainter p(&zoomPixmap);
      p.translate(-xy);
      //m_largeMap->render(&p, QRect(xy, box));
      p.end();
    }

    QPainterPath clipPath;
    clipPath.addEllipse(center, ring, ring);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setClipPath(clipPath);
    p.drawPixmap(corner, zoomPixmap);
    p.setClipping(false);
    p.drawPixmap(corner, maskPixmap);
    p.setPen(Qt::gray);
    p.drawPath(clipPath);
  }
*/
  if (invert) {
    QPainter p(this);
    p.setCompositionMode(QPainter::CompositionMode_Difference);
    p.fillRect(event->rect(), Qt::white);
    p.end();
  }
}

void ZMapWidget::timerEvent(QTimerEvent *) {
  if (!zoomed)
    activateZoom();
  update();
}

void ZMapWidget::mousePressEvent(QMouseEvent *event) {
  if (event->buttons() != Qt::LeftButton)
    return;
  pressed = snapped = true;
  pressPos = dragPos = event->pos();
  //tapTimer.stop();
  //tapTimer.start(HOLD_TIME, this);
}

void ZMapWidget::mouseMoveEvent(QMouseEvent *event) {
  if (!event->buttons())
    return;
  if (!zoomed) {
    if (!pressed || !snapped) {
      QPoint delta = event->pos() - pressPos;
      pressPos = event->pos();
      m_normalMap->pan(delta);
      return;
    } else {
      const int threshold = 10;
      QPoint delta = event->pos() - pressPos;
      if (snapped) {
        snapped &= delta.x() < threshold;
        snapped &= delta.y() < threshold;
        snapped &= delta.x() > -threshold;
        snapped &= delta.y() > -threshold;
      }
      if (!snapped)
        tapTimer.stop();
    }
  } else {
//    dragPos = event->pos();
//    update();
  }
}

void ZMapWidget::mouseReleaseEvent(QMouseEvent *) {
  zoomed = false;
  update();
}

void ZMapWidget::keyPressEvent(QKeyEvent *event) {
  if (!zoomed) {
    if (event->key() == Qt::Key_Left)
      m_normalMap->pan(QPoint(20, 0));
    if (event->key() == Qt::Key_Right)
      m_normalMap->pan(QPoint(-20, 0));
    if (event->key() == Qt::Key_Up)
      m_normalMap->pan(QPoint(0, 20));
    if (event->key() == Qt::Key_Down)
      m_normalMap->pan(QPoint(0, -20));
    if (event->key() == Qt::Key_Z || event->key() == Qt::Key_Select) {
      dragPos = QPoint(width() / 2, height() / 2);
      activateZoom();
    }
  } else {
  /*
    if (event->key() == Qt::Key_Z || event->key() == Qt::Key_Select) {
      zoomed = false;
      update();
    }
    QPoint delta(0, 0);
    if (event->key() == Qt::Key_Left)
      delta = QPoint(-15, 0);
    if (event->key() == Qt::Key_Right)
      delta = QPoint(15, 0);
    if (event->key() == Qt::Key_Up)
      delta = QPoint(0, -15);
    if (event->key() == Qt::Key_Down)
      delta = QPoint(0, 15);
    if (delta != QPoint(0, 0)) {
      dragPos += delta;
      update();
    }
  */
  }
}

void ZMapWidget::zoomIn(int byAmount){
  m_normalMap->zoomIn(byAmount);
}

void ZMapWidget::zoomOut(int byAmount){
  m_normalMap->zoomOut(byAmount);
}

void ZMapWidget::zoomTo(int toLevel){
  m_normalMap->zoomTo(toLevel);
}

bool ZMapWidget::invoke(QString action, QString arg1,QString arg2,QString arg3,
                        QString arg4,   QString arg5,QString arg6){
  if(action == "zoomIn")
    m_normalMap->zoomIn();
  else if(action == "zoomOut")
    m_normalMap->zoomOut();

  return true;
}
