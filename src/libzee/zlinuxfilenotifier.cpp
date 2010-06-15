#include "zlinuxfilenotifier.h"

ZLinuxFileNotifier::ZLinuxFileNotifier()
{
    _ok = false;
    _descriptor = inotify_init();

    if(_descriptor < 0)
        perror("inotify_init");
    else
        _ok = true;
}

bool ZLinuxFileNotifier::watch(QString path, uchar events, bool once){
    int err;
    uint32_t flags = 0;

    if(_ok){
        if(events & FileAccessed)           // accessed
            flags |= IN_ACCESS;
        if(events & FileChanged)            // changed
            flags |= IN_MODIFY;
        if(events & FileOpened)             // opened
            flags |= IN_OPEN;
        if(events & FileClosed)             // closed
            flags |= IN_CLOSE;
        if(events & FileAttributesChanged)  // attrib. change
            flags |= IN_ATTRIB;
        if(events & FileMovedFrom)          // moved from current
            flags |= IN_MOVED_FROM;
        if(events & FileMovedTo)            // moved to current
            flags |= IN_MOVED_TO;
        if(events & FileMoved)              // moved somehow
            flags |= IN_MOVE;
        if(events & FileDeleted)            // deleted
            flags |= IN_DELETE;
        if(events & OwnFileDeleted)         // self deleted
            flags |= IN_DELETE_SELF;
        if(events & OwnFileMoved)           // self moved
            flags |= IN_MOVE_SELF;
        if(events & AnyFileEvent)           // ANY event
            flags |= IN_ALL_EVENTS;

        if(once)                            // remove after first event
            flags |= IN_ONESHOT;
    }

    err = inotify_add_watch(_descriptor,
                            qstrdup(path.toAscii().data()),
                            flags);
    if(err < 0){
        perror("inotify_add_watch");
        return false;
    }else{
        return true;
    }
}
