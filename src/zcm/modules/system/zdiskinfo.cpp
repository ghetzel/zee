#include "zdiskinfo.h"

ZDiskInfo::ZDiskInfo(sigar_t *s, QObject *parent)
    : ZSigarModule(s,parent)
{
    init();
    setObjectName(ZSYS_INFO_DISK);
}

void ZDiskInfo::init(){
    refresh();
}

void ZDiskInfo::refreshFilesystems(){
    if(_sigar){
        sigar_file_system_list_t fsList;
        sigar_file_system_list_get(_sigar, &fsList);

        sigar_file_system_list_destroy(_sigar, &fsList);
    }
}

void ZDiskInfo::refresh(){
    if(_sigar){
        sigar_file_system_list_t fsList;
        sigar_file_system_list_get(_sigar, &fsList);

        for(int i = 0; i < fsList.size; i++){
            if((fsList.data[i].type==SIGAR_FSTYPE_LOCAL_DISK)    ||
               (fsList.data[i].type==SIGAR_FSTYPE_NETWORK)       ||
               (fsList.data[i].type==SIGAR_FSTYPE_RAM_DISK)      ||
               (fsList.data[i].type==SIGAR_FSTYPE_SWAP)          ||
               (fsList.data[i].type==SIGAR_FSTYPE_CDROM))
            {
                ZString devName = ZString(fsList.data[i].dev_name).rightOfLast("/");
                QObject *fs = NULL;

                if(_filesystems.contains(devName)){
                    fs = _filesystems.value(devName);
                }else{
                    fs = new QObject(this);
                    fs->setObjectName(devName);
                    _filesystems.insert(devName, fs);
                }

                if(fs){
                    sigar_file_system_usage_t fsUse;
                    sigar_file_system_usage_get(_sigar, fsList.data[i].dir_name, &fsUse);

                    fs->setProperty("device",       QVariant(fsList.data[i].dev_name));
                    fs->setProperty("mountpoint",   QVariant(fsList.data[i].dir_name));
                    fs->setProperty("flags",        QVariant(CAST(quint32,fsList.data[i].flags)));
                    fs->setProperty("options",      QVariant(fsList.data[i].options));
                    fs->setProperty("filesystem",   QVariant(fsList.data[i].sys_type_name));
                    fs->setProperty("type",         QVariant(fsList.data[i].type_name));
                    fs->setProperty("available",    QVariant(CAST(quint64,fsUse.avail)));
                    fs->setProperty("files",        QVariant(CAST(quint64,fsUse.files)));
                    fs->setProperty("free",         QVariant(CAST(quint64,fsUse.free)));
                    fs->setProperty("freeFiles",    QVariant(CAST(quint64,fsUse.free_files)));
                    fs->setProperty("total",        QVariant(CAST(quint64,fsUse.total)));
                    fs->setProperty("used",         QVariant(CAST(quint64,fsUse.used)));
                    fs->setProperty("use",          QVariant(fsUse.use_percent*100.0));
                    fs->setProperty("qtime",        QVariant(CAST(quint64,fsUse.disk.qtime)));
                    fs->setProperty("queue",        QVariant(CAST(quint64,fsUse.disk.queue)));
                    fs->setProperty("reads",        QVariant(CAST(quint64,fsUse.disk.reads)));
                    fs->setProperty("bytesRead",    QVariant(CAST(quint64,fsUse.disk.read_bytes)));
                    fs->setProperty("rtime",        QVariant(CAST(quint64,fsUse.disk.rtime)));
                    fs->setProperty("serviceTime",  QVariant(fsUse.disk.service_time));
                    fs->setProperty("snapTime",     QVariant(CAST(quint64,fsUse.disk.snaptime)));
                    fs->setProperty("time",         QVariant(CAST(quint64,fsUse.disk.time)));
                    fs->setProperty("writes",       QVariant(CAST(quint64,fsUse.disk.writes)));
                    fs->setProperty("bytesWritten", QVariant(CAST(quint64,fsUse.disk.write_bytes)));
                    fs->setProperty("wtime",        QVariant(CAST(quint64,fsUse.disk.wtime)));
                }
            }
        }

        sigar_file_system_list_destroy(_sigar, &fsList);
    }
}
