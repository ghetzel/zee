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

#ifndef ZMETAREADER_H
#define ZMETAREADER_H

#define ZCM_METAREADER      "zee:metareader"
#define ZCM_METAPROPERTY    "zee:metaproperty"

#include <QtCore>
#include <zeventmanager.h>
#include <zconfigurable.h>
#include <zmetaparser.h>
#include <metaparsers/zaudiometaparser.h>

struct ZMetadata{
    QString name;
    QString type;
    QString key;
};

class ZMetaReader : public QObject, public ZConfigurable
{
    Q_OBJECT
public:
    ZMetaReader(const ZConfig &el, QObject *parent=0);

public slots:
    void setFileName(QString location);

signals:
    void fileChanged(QString location);
    void dataChanged();

private:
    void init();
    void parse(const ZConfig &el);
    void fetchMetadata();

private:
    QList<ZMetadata> _fields;
    QHash<QString,ZMetaParser*> _parsers;
    QFile _source;
    QObject *_dataObject;
};

#endif // ZMETAREADER_H
