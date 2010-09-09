#ifndef ZSEEKBAR_H
#define ZSEEKBAR_H

#define ZUI_SEEKBAR	"zui:seekbar"

#include <QtCore>
#include <zeventmanager.h>
#include <zui/zwidget.h>
#include <zui/modules/form/zprogressbar.h>

class ZSeekbar : public ZProgressBar
{
    Q_OBJECT
public:
    ZSeekbar(const ZConfig &el, QWidget *parent=0);
    void parse(const ZConfig&);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

public slots:
    void reset();
    void addBookmark(qint64 msec);

signals:
    void positionChanged(qint64);

private:
    void init();

private:
    QList<qint64> _bookmarks;
};

#endif // ZSEEKBAR_H
