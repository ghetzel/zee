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

#ifndef ZFILENOTIFIER_H
#define ZFILENOTIFIER_H

#include <QtCore>

/*!
  \class ZFileNotifier
  \ingroup libzee

  \brief A class for watching filesystem-level changes to files and directories.
*/
class ZFileNotifier : public QObject{
  Q_OBJECT
  Q_ENUMS(ZFileEvents);

public:
  enum ZFileEvents{
    AnyFileEvent            = 1,
    FileAccessed            = 1<<1,
    FileChanged             = 1<<2,
    FileAttributesChanged   = 1<<3,
    FileOpened              = 1<<4,
    FileClosed              = 1<<5,
    FileMoved               = 1<<6,
    FileMovedFrom           = 1<<7,
    FileMovedTo             = 1<<8,
    FileDeleted             = 1<<9,
    FileCreated             = 1<<10,
    OwnFileDeleted          = 1<<11,
    OwnFileMoved            = 1<<12
  };

  ZFileNotifier(){};

  virtual bool watch(QString path, ZFileEvents event, bool once=false) =0;

  virtual bool watch(QFile fpath, ZFileEvents event, bool once=false){
    return watch(fpath.fileName(), event, once);
  };
  virtual bool watch(QDir dpath, ZFileEvents event, bool once=false){
    return watch(dpath.absolutePath(), event, once);
  };

signals:
  void fileChanged(QString path);
};

#endif // ZFILENOTIFIER_H
