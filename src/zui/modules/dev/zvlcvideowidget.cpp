#include "zvlcvideowidget.h"

ZVLCVideoWidget::ZVLCVideoWidget(QWidget *parent)
  : ZVideoWidget(parent){
  init();
}

ZVLCVideoWidget::ZVLCVideoWidget(QString uri, QWidget *parent)
  : ZVideoWidget(parent){
  init();
  setContentSource(uri);
}

ZVLCVideoWidget::~ZVLCVideoWidget(){
  stop();
  libvlc_media_player_release(vlcPlayer);
  libvlc_release(vlcInstance);
}

void ZVLCVideoWidget::init(){
//set VLC arguments
  const char * const vlc_args[] =
  {
    "-I", "dummy",
    "--ignore-config",                // Don't use VLC's config.
    "--extraintf=logger",             // Log anything.
    "--verbose=1",
    "--no-x11-shm",
    "--no-glx-shm",
    "--no-xvideo-shm",
    "--no-osd",
    "--vout", "xvideo"
    //,"--plugin-path=/usr/lib/vlc"
  };

  setSizePolicy(QSizePolicy(QSizePolicy::Expanding,
                            QSizePolicy::Expanding,
                            QSizePolicy::Frame));

  mediaSize = QSize(480,300);
  setMinimumSize(mediaSize.width(), mediaSize.height());

//init VLC...
//exception handler
  libvlc_exception_init(&vlcException);
//VLC instance
  vlcInstance = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]),
                           vlc_args,
                           &vlcException);
  raise(&vlcException);

//VLC player
  vlcPlayer = libvlc_media_player_new(vlcInstance, &vlcException);
  raise(&vlcException);

}


void ZVLCVideoWidget::update(){
//only emit media updates if it's actually playing...
  if(currentState != Playing)
    return;

//get current media
  libvlc_media_t *cMedia = libvlc_media_player_get_media(vlcPlayer,
                                                         &vlcException);
  libvlc_exception_clear(&vlcException);

//if no media is loaded...
  if(cMedia == NULL){
    stop();
  }else{
    emit positionChanged(libvlc_media_player_get_position(vlcPlayer,
                                                          &vlcException));
    emit volumeChanged(libvlc_audio_get_volume(vlcInstance,
                                               &vlcException));
  }
}

void ZVLCVideoWidget::play(){
  libvlc_media_player_play(vlcPlayer, &vlcException);
  emit playstateChanged(Playing);
}

void ZVLCVideoWidget::pause(){
  libvlc_media_player_pause(vlcPlayer, &vlcException);
  emit playstateChanged(Paused);
}

void ZVLCVideoWidget::stop(){
  libvlc_media_player_stop(vlcPlayer, &vlcException);
  emit positionChanged(libvlc_media_player_get_position(vlcPlayer,
                                                        &vlcException));
  emit playstateChanged(Stopped);
}

void ZVLCVideoWidget::setVolume(int volume){
  cVolume = volume;
  libvlc_audio_set_volume(vlcInstance,
                          cVolume,
                          &vlcException);
  emit setVolume(cVolume);
}

void ZVLCVideoWidget::setPosition(qreal position){
  cPosition = position;
  libvlc_media_player_set_position(vlcPlayer,
                                   cPosition,
                                   &vlcException);
  emit positionChanged(cPosition);
}

QSize ZVLCVideoWidget::sizeHint() const
{
  return mediaSize;
}


QSize ZVLCVideoWidget::minimumSizeHint() const
{
  return mediaSize;
}

void ZVLCVideoWidget::setContentSource(QString uri){
  _uri = uri;

//load media
  vlcMedia = libvlc_media_new(vlcInstance,
                              uri.toAscii(),
                              &vlcException);
  raise(&vlcException);

//tell player about loaded media
  libvlc_media_player_set_media(vlcPlayer, vlcMedia, &vlcException);
  raise(&vlcException);

//prepare drawing of media on the widget
#if defined(Q_OS_WIN)
  libvlc_media_player_set_drawable(vlcPlayer,
                                   reinterpret_cast<unsigned int>(winId()),
                                   &vlcException);
//#elif defined(Q_OS_MAC)
#else
  libvlc_media_player_set_drawable(vlcPlayer, winId(), &vlcException);
#endif
  raise(&vlcException);

  emit contentSourceChanged(uri);
}

bool ZVLCVideoWidget::invoke(QString action, QString arg1, QString arg2,
                          QString arg3,QString arg4,QString arg5,QString arg6){

  if(action == "control"){
    if(arg1 == "play")
      play();
    else if(arg1 == "pause")
      pause();
    else if(arg1 == "stop")
      stop();
  }

  return true;
}

void ZVLCVideoWidget::raise(libvlc_exception_t *ex)
{
  if(libvlc_exception_raised(ex))
    //std::cout << "Error: " << libvlc_exception_get_message(ex) << std::endl;
  libvlc_exception_clear(ex);
}
