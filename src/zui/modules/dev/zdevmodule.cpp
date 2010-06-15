#include "zdevmodule.h"

ZDevModule::ZDevModule()
{
  //ZuiUtils::registerContainerElement("zui:video");
}

ZuiResult ZDevModule::prepareWidget(const QDomElement *el,
                                       QWidget *currentWidget,
                                       QWidget *parentWidget){
  ZuiResult zRes;
  zRes.parent = parentWidget;
  QWidget *newWidget = NULL;

  if(el->tagName() == "zui:d_scene"){
    //QGraphicsScene *scene = new QGraphicsScene;

    //scene->addRect(1.0, 1.0, 100.0, 200.0, QPen(Qt::black), QBrush(Qt::green));

    //scene->addWidget(new QPushButton("test", zRes.parent));

    //newWidget = new QGraphicsView(scene, zRes.parent);

    //newWidget->setLayout(ZuiUtils::getLayout(
    //  el->attribute("layout", ZUI_DEFAULT_LAYOUT)));


    //static_cast<QGraphicsView*>(newWidget)->setScene(scene);
    //newWidget = new ClutterQt(zRes.parent);

  }else if(el->tagName() == "zui:dttest"){
    newWidget = QApplication::desktop()->screen(QApplication::desktop()->primaryScreen());

    newWidget->setWindowFlags(Qt::Desktop);
    newWidget->setWindowFlags(Qt::FramelessWindowHint);
    newWidget->setLayout(new QHBoxLayout);

    newWidget->layout()->addWidget(new QPushButton("Test 1234", newWidget));

  }else if(el->tagName() == "zui:video"){
    if(el->hasAttribute("backend")){
      if(el->attribute("backend") == "vlc"){
        newWidget = new ZVLCVideoWidget(el->attribute("uri", NULL),
                                        zRes.parent);
      }else{
        newWidget = new ZPhononVideoWidget(el->attribute("uri", NULL),
                                           zRes.parent);
      }
    }

    /*
  //	set layout
  /    newWidget->setLayout(ZuiUtils::getLayout(
  \      el->attribute("layout", ZUI_DEFAULT_LAYOUT)));
   \
    \  zRes.parent = newWidget;
*/  //


  }else if(el->tagName() == "zui:qmlscene"){
    if(el->hasAttribute("file")){
      newWidget = new QmlView(zRes.parent);

      if(el->attribute("autofill", "true") == "true")
        static_cast<QmlView*>(newWidget)->setContentResizable(true);

      static_cast<QmlView*>(newWidget)->viewport()->setAutoFillBackground(false);

      if(QFile::exists(el->attribute("file",""))){
        QFile qmlFile(el->attribute("file",""));

        if(qmlFile.open(QIODevice::ReadOnly)){
          QTextStream qml(&qmlFile);
          static_cast<QmlView*>(newWidget)->setQml(qml.readAll());
          static_cast<QmlView*>(newWidget)->execute();
          qmlFile.close();
        }
      }
    }
  }else if(el->tagName() == "zee:action"){
    ZWidget *zW = dynamic_cast<ZWidget*>(zRes.parent);

    if(zW){
        if(el->hasAttribute("when"))    // When
            zW->addAction(ZWidget::When, el->attribute("do"), el->attribute("when"));

        if(el->hasAttribute("on"))      // On
            zW->addAction(ZWidget::On, el->attribute("do"), el->attribute("on"));

        if(el->hasAttribute("every"))   // Every
            zW->addAction(ZWidget::Every, el->attribute("do"), el->attribute("every"));
    }
  }else if(el->tagName() == "zui:zonky"){


  }
  zRes.widget = newWidget;
  return zRes;
}

Q_EXPORT_PLUGIN2(zmod_dev, ZDevModule)
