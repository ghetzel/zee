#ifndef ZDEBUG_H
#define ZDEBUG_H

#include <QCoreApplication>
#include <zutil.h>
#include <libzee/libzee.h>
#include <QGtkStyle>
#include <QIcon>
#include <QtCore>


class ZDebug : public QCoreApplication
{
public:
    ZDebug(int argc, char **argv);
};

#endif // ZDEBUG_H
