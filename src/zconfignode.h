#ifndef ZCONFIGNODE_H
#define ZCONFIGNODE_H

#include <QObject>
#include <QDomNode>

class ZConfigNode : public QDomNode
{
public:
    ZConfigNode();
    ZConfigNode(const QDomNode &node);
    QObject *object();
    void setObject(QObject *object);

private:
    QObject *_object;
};

#endif // ZCONFIGNODE_H
