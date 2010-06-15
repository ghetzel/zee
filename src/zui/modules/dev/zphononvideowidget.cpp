#include "zphononvideowidget.h"

ZPhononVideoWidget::ZPhononVideoWidget(QWidget *parent)
  : ZVideoWidget(parent){
  init();
}

ZPhononVideoWidget::ZPhononVideoWidget(QString uri, QWidget *parent)
  : ZVideoWidget(parent){
  init();
  setContentSource(uri);
}

void ZPhononVideoWidget::init(){
  vWidget = new VideoWidget(this);
  //setLayout(new QVBoxLayout);
  //layout()->addWidget(vWidget);

  _mo = new MediaObject;
  _audio = new AudioOutput(Phonon::VideoCategory, parent());

  Phonon::createPath(_mo, vWidget);
  Phonon::createPath(_mo, _audio);

  _inputPaths = _audio->inputPaths();
  _outputPaths = _mo->outputPaths();

}

void ZPhononVideoWidget::setContentSource(QString uri){
  _uri = uri;
  _mo->setCurrentSource(MediaSource(_uri));
  emit contentSourceChanged(uri);
}

void ZPhononVideoWidget::play(){
  _mo->play();
  emit playstateChanged(Playing);
}

void ZPhononVideoWidget::pause(){
  _mo->pause();
  emit playstateChanged(Paused);
}

void ZPhononVideoWidget::stop(){
  _mo->stop();
  emit playstateChanged(Stopped);
}

bool ZPhononVideoWidget::invoke(QString action, QString arg1, QString arg2,
                          QString arg3,QString arg4,QString arg5,QString arg6){

  if(action == "control"){
    if(arg1 == "play")
      play();
    else if(arg1 == "pause")
      pause();
    else if(arg1 == "stop")
      stop();
  }else if(action == "open"){
    setContentSource(arg1);
  }

  return true;
}

