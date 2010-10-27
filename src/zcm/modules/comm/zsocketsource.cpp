#include "zsocketsource.h"

ZSocketSource::ZSocketSource(QObject *parent)
    : QObject(parent)
{
    _fileDescriptor = -1;
    _readNotifier = NULL;
    _writeNotifier = NULL;
}

ZSocketSource::~ZSocketSource(){
//    qDebug() << "KILL SOCKET (fd: " << _fileDescriptor << ")";

    if(_readNotifier && _readNotifier->isEnabled())
        _readNotifier->setEnabled(false);
    if(_writeNotifier && _writeNotifier->isEnabled())
        _writeNotifier->setEnabled(false);
}

void ZSocketSource::setReadNotify(guint fd){
//    qDebug() << "READING SOCKET (fd: " << fd << ")";

    if(_fileDescriptor < 0)
        _fileDescriptor = fd;
    else
        Q_ASSERT(_fileDescriptor == fd);

    if(!_readNotifier)
        _readNotifier = new QSocketNotifier(fd, QSocketNotifier::Read, this);

    connect(_readNotifier, SIGNAL(activated(int)),
            this,          SLOT(socketRead(int)));
}

void ZSocketSource::setWriteNotify(guint fd){
//    qDebug() << "WRITING SOCKET (fd: " << fd << ")";

    if(_fileDescriptor < 0)
        _fileDescriptor = fd;
    else
        Q_ASSERT(_fileDescriptor == fd);

    if(!_writeNotifier)
        _writeNotifier = new QSocketNotifier(fd, QSocketNotifier::Write, this);

    connect(_writeNotifier, SIGNAL(activated(int)),
            this,           SLOT(socketWritten(int)));
}

void ZSocketSource::setSourceFunc(PurpleInputFunction func, gpointer data){
    _func = func;
    _data = data;
}

void ZSocketSource::socketRead(int fd){
    if(_func)
        _func(_data, fd, purpleInputCondition());
}

void ZSocketSource::socketWritten(int fd){
    if(_func)
        _func(_data, fd, purpleInputCondition());
}

int ZSocketSource::socket(){
    return _fileDescriptor;
}

PurpleInputCondition ZSocketSource::purpleInputCondition(){
    int cond = 0;

    if(_readNotifier)
        cond |= PURPLE_INPUT_READ;
    if(_writeNotifier)
        cond |= PURPLE_INPUT_WRITE;

    return (PurpleInputCondition)cond;
}
