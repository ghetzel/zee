#include "zmapwidget.h"

ZMapWidget::ZMapWidget(QWidget *parent)
  : MapControl(QSize(QApplication::desktop()->width(),
                     QApplication::desktop()->height())){
  this->setParent(parent);
  init();
}

void ZMapWidget::init()
{
  //enablePersistentCache();
// 	control = new MapControl(size());
  adapter = new OSMMapAdapter();
  //adapter = new OpenAerialMapAdapter();
  //adapter = new GoogleMapAdapter();
  //adapter = new YahooMapAdapter();
  //adapter = new TileMapAdapter("127.0.0.1", "/maps?map=/var/www/zee/osm.map&layers=all&mode=tile&tilemode=gmap&tile=%2+%3+%1", 256,0,17);
//	setup layers
  layers.insert("main", new MapLayer("OpenStreetMap-Layer", adapter, false));
  setupLayers();

// 	setLayout(new QHBoxLayout);
//	control->setLayout(layout());
// 	layout()->addWidget(control);
//  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  //connect(this, SIGNAL(viewChanged(QPointF, int)), SLOT(parseViewDetails(QPointF,int)));
}

void ZMapWidget::parseViewDetails(QPointF point, int zoom)
{
  emit viewChanged(QVariant(point.x()).toString() + "  " + QVariant(point.y()).toString() + " +" + QString(zoom));
}

void ZMapWidget::setupLayers()
{
  foreach(Layer *layer, layers)
    addLayer(layer);
}

bool ZMapWidget::invoke(QString action)
{
  if(action == "zoomIn")
    zoomIn();
  else if(action == "zoomOut")
    zoomOut();
  return true;
}

QSize ZMapWidget::sizeHint()
{
  if(layout())
    return QSize(600,350);
  return QSize(0,0);
}

void ZMapWidget::resizeEvent(QResizeEvent *event)
{
  resize(event->size());
}

/*
QHash<QString,QVariant> ZMapWidget::getInfoAtPoint(QPointF point, int zoom)
{
  QSqlQuery q(zeedb);
  QHash<QString,QVariant> ret;

  q.prepare("SELECT Z_GetRoadAtCoords(:x, :y)");
  q.bindValue(":x", point.x());
  q.bindValue(":y", point.y());

  if(q.exec()){
    if(q.next())
      if(q.value(0).isValid() && !q.value(0).isNull())
        ret.insert("road", q.value(0));
  }else{
    //cout << "SQL: Error:" << q.lastError().databaseText().toStdString() << endl; flush(cout);
  }

  emit infoUpdated(ret);
  return ret;
}
*/
