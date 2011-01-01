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

#ifndef ZPOLYSTATEINDICATOR_H
#define ZPOLYSTATEINDICATOR_H

#define ZUI_POLYSTATE       "zui:icon"

#define ZPOLYIC_PAD_X       2
#define ZPOLYIC_PAD_Y       2

#include <QLabel>
#include <zeventmanager.h>
#include <zui/zwidget.h>

class ZPolystateIndicator : public QLabel, public ZWidget
{
    Q_OBJECT
    Q_PROPERTY(QString state READ state WRITE switchTo)

public:
    ZPolystateIndicator(const ZConfig &el, QWidget *parent=0);
    void parse(const ZConfig &el);
    QString state();
    QPixmap currentImage();
    void resizeEvent(QResizeEvent*);

signals:
    void stateChanged(QString);

public slots:
    void setImage(QString name, QString icon);
    void switchTo(QString name);
    void setValue(double value);
    void reset();
    void clear();

private:
    void init();

private:
    double _value;
    QHash<QString,QIcon> _images;
    QHash<QString,QPair<double,double> > _ranges;
    QString _defaultState;
    QString _currentState;
};

#endif // ZPOLYSTATEINDICATOR_H
