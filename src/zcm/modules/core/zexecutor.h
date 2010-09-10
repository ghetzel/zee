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

#ifndef ZEXECUTOR_H
#define ZEXECUTOR_H

#define ZCM_EXECUTOR    "zee:executor"

#include <QString>
#include <zutil.h>
#include <zconfigurable.h>
#include <zeventmanager.h>

class ZExecutor : public QObject, public ZConfigurable
{
    Q_OBJECT
    Q_PROPERTY(QString lastOutput READ lastOutput)
public:
    ZExecutor(const ZConfig &el, QObject *parent=0);
    ~ZExecutor();
    QString lastOutput();

public slots:
    void exec();
    void setCommand(QString);

signals:
    void executed(QString);
    void commandChanged(QString,QString="");

private:
    void parse(const ZConfig &el);

private:
    QString _command;
    QString _oneLine;
    QString _lastOutput;
};

#endif // ZEXECUTOR_H
