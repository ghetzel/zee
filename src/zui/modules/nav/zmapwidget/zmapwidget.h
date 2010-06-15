#ifndef ZMAPWIDGET_H
#define ZMAPWIDGET_H

#include <iostream>
#include <QtCore>
#include <QtGui>
#include "slippymap.h"
#include "zevent.h"

#define ZMAP_DEFAULT_WIDTH 300
#define ZMAP_DEFAULT_HEIGHT 300

class ZMapWidget : public QWidget, public ZEvent
{
    Q_OBJECT

public:
    ZMapWidget(QWidget *parent = 0);
    void setCenter(qreal lat, qreal lng);
    void setCenter(QPointF &point);
    QSize sizeHint();

public slots:
    void toggleNightMode();
    void zoomIn(int byAmount = 1);
    void zoomOut(int byAmount = 1);
    void zoomTo(int toLevel);
    bool invoke(QString action,
                QString arg1="",QString arg2="",QString arg3="",
                QString arg4="",QString arg5="",QString arg6="");

private slots:
    void updateMap(const QRect &r);

protected:
    void activateZoom();
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *event);

private:
    SlippyMap *m_normalMap;
    SlippyMap *m_largeMap;
    bool pressed;
    bool snapped;
    QPoint pressPos;
    QPoint dragPos;
    QBasicTimer tapTimer;
    bool zoomed;
    QPixmap zoomPixmap;
    QPixmap maskPixmap;
    bool invert;
};

#endif // ZMAPWIDGET_H
