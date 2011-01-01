#ifndef ZCONFIGELEMENT_H
#define ZCONFIGELEMENT_H

#include <QList>
#include <QDomElement>

class ZConfigElement : public QDomElement
{
public:
    ZConfigElement();
    ZConfigElement(const QDomElement &el);
    //ZConfigElement &operator=(const QDomElement &other);
    QList<ZConfigElement> children(QString tagName=QString()) const;
    QString value() const;
};

#endif // ZCONFIGELEMENT_H
