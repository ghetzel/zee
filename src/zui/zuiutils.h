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

#ifndef ZUIUTILS_H
#define ZUIUTILS_H

#define ZUI_DEFAULT_LAYOUT              "horizontal"
#define ZUI_FAILOVER_LAYOUT             QHBoxLayout

#define ZCONFIG_ATTRIB_BOOL_TRUE        "true|1|yes|on"
#define ZCONFIG_ATTRIB_BOOL_FALSE       "false|0|no|off"
#define ZCONFIG_ATTRIB_CARD_E           "e|east"
#define ZCONFIG_ATTRIB_CARD_N           "n|north"
#define ZCONFIG_ATTRIB_CARD_NE          "ne|northeast"
#define ZCONFIG_ATTRIB_CARD_NW          "nw|northwest"
#define ZCONFIG_ATTRIB_CARD_S           "s|south"
#define ZCONFIG_ATTRIB_CARD_SE          "se|southeast"
#define ZCONFIG_ATTRIB_CARD_SW          "sw|southwest"
#define ZCONFIG_ATTRIB_CARD_W           "w|west"
#define ZCONFIG_ATTRIB_ALIGN_RIGHT      "right"
#define ZCONFIG_ATTRIB_ALIGN_LEFT       "left"
#define ZCONFIG_ATTRIB_ALIGN_CENTER     "center"
#define ZCONFIG_ATTRIB_ALIGN_JUSTIFY    "justify"
#define ZCONFIG_ATTRIB_ALIGN_HCENTER    "hcenter"
#define ZCONFIG_ATTRIB_ALIGN_VCENTER    "vcenter"
#define ZCONFIG_ATTRIB_ALIGN_TOP        "top"
#define ZCONFIG_ATTRIB_ALIGN_BOTTOM     "bottom"
#define ZCONFIG_ATTRIB_SEV_DEBUG	"debug|debugging|d"
#define ZCONFIG_ATTRIB_SEV_INFO		"info|information|i"
#define ZCONFIG_ATTRIB_SEV_WARN		"warn|warning|w"
#define ZCONFIG_ATTRIB_SEV_ERROR	"err|error|e"
#define ZCONFIG_ATTRIB_SEV_CRIT		"crit|critical|c"
#define ZCONFIG_ATTRIB_SEV_QUESTION	"question|help|q"
#define ZCONFIG_ATTRIB_RAD_CLOCK        "fwd|forward|right|clockwise|cw"
#define ZCONFIG_ATTRIB_RAD_CNTCLOCK     "rev|reverse|left|counterclockwise|ccw"

#define ZUI_HORIZON_LAYOUT              "horizontal"
#define ZUI_VERTICAL_LAYOUT             "vertical"
#define ZUI_FORM_LAYOUT                 "form"
#define ZUI_GRID_LAYOUT                 "grid"
#define ZUI_FLOW_LAYOUT                 "flow"
#define ZUI_BORDER_LAYOUT                "border"

#include <iostream>
#include <QtCore>
#include <QtGui>
#include <QDomElement>
#include <QList>

#include <zutil.h>
#include "layouts/zflowlayout.h"
#include "layouts/zborderlayout.h"

namespace ZuiUtilsNS{
  struct ActionDescriptor{
    QString receiver;
    QString action;
    QStringList arguments;
  };

  struct ConditionString{
    QString handler;
    QString property;
    QString comparator;
    QString value;
  };

  enum FileInfo{
    FilePath,
    FileName,
    BaseFileName,
    FileSize,
    FileModificationDate,
    FileCreationDate,
    FileParentDirectory
  };

  enum MediaStates{
    Playing,
    Stopped,
    Paused,
    Opening,
    Buffering,
    Seeking
  };
};

using namespace std;
using namespace ZuiUtilsNS;

/*!
  \class ZuiUtils
  \ingroup zui
  \brief A set of utility functions for constructing UI elements.
*/
class ZuiUtils
{
  Q_ENUMS(FileInfo)
  Q_ENUMS(MediaStates)

private:
  static QList<QString> _containers;

public:
  enum ZConfigAttribOption{
      AlignBottom,
      AlignCenter,
      AlignHCenter,
      AlignJustify,
      AlignLeft,
      AlignRight,
      AlignTop,
      AlignVCenter,
      BooleanFalse,
      BooleanTrue,
      CardinalEast,
      CardinalNorth,
      CardinalNorthEast,
      CardinalNorthWest,
      CardinalSouth,
      CardinalSouthEast,
      CardinalSouthWest,
      CardinalWest,
      SeverityCritical,
      SeverityDebug,
      SeverityError,
      SeverityInfo,
      SeverityQuestion,
      SeverityWarning,
      RadialDirectionClockwise,
      RadialDirectionCounterClockwise
  };

public:

/*!
  Should be called once when the program initializes
*/
  static void initialize();

/*!
  Returns a list of registered container elements.
*/
  static QList<QString> getContainerNames();

/*!
  Registers a DOM element's \a tagName as a container (i.e.: able to contain
  child elements)
*/
  static void registerContainerElement(QString tagName);

/*!
  Registers a list of DOM element's tag names as containers.
*/
  static void registerContainerElements(QList<QString> elements);

/*!
  Returns an instance of a QLayout derivate based on a string \a id.
*/
  static QLayout *getLayout(QString id);

/*!
  Returns the Qt::Alignment enum value for the given configuration value
*/
  static Qt::Alignment getAlignment(QString configVal);

/*!
  Returns a QIcon by filename, freedesktop.org-compliant theme
*/
  static QIcon getIcon(QString name);

/*!
  Returns true if \a source is an acceptable value of \a option
*/
  static bool attribute(QString source, ZConfigAttribOption option);

/*!
  Checks for the presence of and truthiness of an attribute \a name in \a el
*/
  static bool attributeTrue(QString);

/*!
  Checks for the presence of and falsitude of an attribute \a name in \a el
*/
  static bool attributeFalse(QString);

/*!
  Checks for the presence of and matchiness of an attribute \a name to \a match
  in \a el.
*/
  static bool attributeEquals(QDomElement el, QString name, QVariant match);
};

#endif // ZUIUTILS_H
