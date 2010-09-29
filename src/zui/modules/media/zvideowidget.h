/******************************************************************************
*    This file is part of Zee.
*
*    Zee is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    Zee is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with Zee.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#ifndef ZVIDEOWIDGET_H
#define ZVIDEOWIDGET_H

#define	ZUI_VIDEO		"zui:video"

#define	ZVIDEO_AUDIO_BITRATE    "audioBitrate"
#define	ZVIDEO_AUDIO_FORMAT	"audioFormat"
#define	ZVIDEO_FPS		"fps"
#define	ZVIDEO_LENGTH		"length"
#define	ZVIDEO_AUDIO_CHANNELS	"channels"
#define	ZVIDEO_SAMPLE_RATE	"samplerate"
#define	ZVIDEO_SEEKABLE		"seekable"
#define	ZVIDEO_SIZE		"size"
#define	ZVIDEO_TAGS		"tags"
#define	ZVIDEO_BITRATE		"bitrate"
#define	ZVIDEO_FORMAT		"format"
#define ZVIDEO_WIDTH		"width"
#define ZVIDEO_HEIGHT		"height"

#include <qmpwidget/qmpwidget.h>
#include <zeventmanager.h>
#include <zui/zwidget.h>

//using namespace Phonon;

class ZVideoWidget : public QMPwidget, public ZWidget
{
    Q_OBJECT
public:
    ZVideoWidget(const ZConfig &el, QWidget *parent=0);

signals:
    void sourceChanged(QString);
    void positionChanged(qint64);
    void dataChanged();

private slots:
    void _streamPositionChanged(double);
    void _updateMediaInfo(QMPwidget::MediaInfo);

private:
    void init();
    void parse(const ZConfig&);

private:
    QObject *_dataObject;
};

#endif // ZVIDEOWIDGET_H
