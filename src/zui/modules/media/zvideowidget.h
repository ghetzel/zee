#ifndef ZVIDEOWIDGET_H
#define ZVIDEOWIDGET_H

#define	ZUI_VIDEO	    "zui:video"

#include <Phonon/VideoPlayer>
#include <zeventmanager.h>
#include <zui/zwidget.h>

using namespace Phonon;

class ZVideoWidget : public ZWidget<VideoPlayer>
{
    Q_OBJECT
public:
    ZVideoWidget(const ZConfig &el, QWidget *parent=0);

signals:
    void sourceChanged(QString);

public slots:
    void load(QString location);

private:
    void init();
    void parse(const ZConfig &el);

private:
    MediaSource *_source;
};

#endif // ZVIDEOWIDGET_H
