#include "zstyle.h"

void ZStyleProxy::drawControl(ControlElement element, const QStyleOption *option,
                         QPainter *painter, const QWidget *widget) const
{
//  disable focus rectangle draw on buttons
    if(element == CE_PushButton){
        const QStyleOptionFocusRect *r = qstyleoption_cast<const QStyleOptionFocusRect*>(option);
        QStyleOptionFocusRect *focrec = (QStyleOptionFocusRect*)r;
        if(focrec->type & QStyleOptionFocusRect::SO_FocusRect){
            focrec->backgroundColor = Qt::transparent;
        }
    }
}
