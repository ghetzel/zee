#ifndef ZMAP_WIDGET_
#define ZMAP_WIDGET_

#define ZDB_GID_CNAME		"z_db_gis"
#define ZDB_GIS_DRIVER		"QPSQL"
#define ZDB_GIS_HOSTNAME	"localhost"
#define ZDB_GIS_USERNAME	"gis"
#define ZDB_GIS_PASSWORD	"gis"
#define ZDB_GIS_DATABASE	"gis"

#include <iostream>
#include <QtCore>
#include <QtGui>
#include <QList>
#include <QHash>
#include <QSize>
#include <QMapControl/qmapcontrol.h>
#include <zevent.h>

using namespace qmapcontrol;

class ZMapWidget : public MapControl, public ZEvent
{
  Q_OBJECT

  public:
    ZMapWidget(QWidget *parent);
    void init();
    bool invoke(QString action);
    QSize sizeHint();
    void resizeEvent(QResizeEvent *event);

  public slots:
    QHash<QString,QVariant> getInfoAtPoint(QPointF point, int zoom);

  private:
    void setupLayers();

  private:
    MapAdapter *adapter;
    QHash<QString, Layer*> layers;

  private slots:
    void parseViewDetails(QPointF,int);

  signals:
    void viewChanged(QString);
    void infoUpdated(QHash<QString,QVariant>);
};

#endif
