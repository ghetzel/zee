#include "zchatclient.h"

ZChatClient::ZChatClient(const ZConfig &el, QObject *parent)
    : QObject(parent),
      ZComponent(el,this)
{
    parse(_config);
}

void ZChatClient::parse(const ZConfig &el){

}
