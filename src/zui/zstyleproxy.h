#ifndef ZSTYLE_H
#define ZSTYLE_H

#include <QtGui>

class ZStyleProxy : public QProxyStyle
{
public:
    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
};

#endif // ZSTYLE_H
