#include "zchataccount.h"

ZChatAccount::ZChatAccount()
{}

ZChatAccount::ZChatAccount(QString user, QString pass, QString protocol){
    setUsername(user);
    setPassword(pass);
    setProtocol(protocol);
}

void ZChatAccount::setUsername(QString user){
    _username = user;
    checkAndSetAccount();
}

void ZChatAccount::setPassword(QString pass){
    _password = pass;
    checkAndSetAccount();
}

void ZChatAccount::setProtocol(QString protocol){
    if(ZString::leftOf(protocol,"-") == ZCHAT_PURPLE_PROTO_TAG){
        _protocol = protocol;
    }else{
        _protocol = QString(ZCHAT_PURPLE_PROTO_TAG)+QString("-")+_protocol;
    }

    checkAndSetAccount();
}

void ZChatAccount::setState(bool s){
    purple_account_set_enabled(_account, ZEE_OBJNAME, s);
}

void ZChatAccount::enable(){
    setState(true);
}

void ZChatAccount::disable(){
    setState(false);
}

void ZChatAccount::checkAndSetAccount(){
    if(!(_username.isEmpty() &&
         _password.isEmpty() &&
         _protocol.isEmpty())){

        _account = purple_account_new(username(), protocol());
        purple_account_set_password(_account, password());
        purple_accounts_add(_account);
    }
}

const char *ZChatAccount::username(){
    return CSTR(_username);
}
const char *ZChatAccount::password(){
    return CSTR(_password);
}

const char *ZChatAccount::protocol(){
    return CSTR(_protocol);
}

PurpleAccount *ZChatAccount::account(){
    return _account;
}
