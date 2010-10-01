#include "zconfignode.h"

ZConfigNode::ZConfigNode()
    : QDomNode(){
    _object = NULL;
}

ZConfigNode::ZConfigNode(const QDomNode &node)
    : QDomNode(node)
{
    _object = NULL;
}

void ZConfigNode::setObject(QObject *object){
    _object = object;
}

QObject *ZConfigNode::object(){
    return _object;
}
