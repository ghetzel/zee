#include "zconfigelement.h"

ZConfigElement::ZConfigElement()
    : QDomElement()
{}


ZConfigElement::ZConfigElement(const QDomElement &el)
    : QDomElement(el){

}

QList<ZConfigElement> ZConfigElement::children(QString tagName) const{
    QList<ZConfigElement> rv;
    QDomNodeList nodes = childNodes();

    for(int i = 0; i < nodes.count(); i++){
        if(nodes.at(i).isElement()){
            QDomElement cel = nodes.at(i).toElement();
            if(tagName.isEmpty() ||
               (!tagName.isEmpty() && cel.tagName() == tagName))
            {
                rv << cel;
            }
        }
    }

    return rv;
}

QString ZConfigElement::value() const{
    if(hasAttribute("value"))
        return attribute("value");
    return text();
}
