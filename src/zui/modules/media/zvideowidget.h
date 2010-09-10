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
    void parse(const ZConfig&);

private:
    MediaSource *_source;
};

#endif // ZVIDEOWIDGET_H
