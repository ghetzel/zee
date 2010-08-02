#include "zextrasmodule.h"

ZExtrasModule::ZExtrasModule()
{
  //ZuiUtils::registerContainerElement(ZUI_WEBBROWSER);
}

ZuiResult ZExtrasModule::prepareWidget(const QDomElement &el, QWidget *parent){
  ZuiResult zRes;
  zRes.parent = parent;
  zRes.widget = NULL;

#ifdef ZUI_CLOCK // clock: tempus fugit
  if(el.tagName() == ZUI_CLOCK){
    if(el.hasAttribute("timeformat"))
      if(el.hasAttribute("dateformat")) // time & date format specified
	zRes.widget = new ZClock(el.attribute("timeformat"),
			       el.attribute("dateformat"),
			       zRes.parent);
      else // only time format specified
	zRes.widget = new ZClock(el.attribute("timeformat"), zRes.parent);
    else // no formats specified
      zRes.widget = new ZClock(zRes.parent);
#endif // ZUI_CLOCK
#ifdef ZUI_FILEBROWSER
  }else if(el.tagName() == ZUI_FILEBROWSER){
    if(el.hasAttribute("dir"))
      zRes.widget = new ZFileBrowser(el, zRes.parent);

#endif // ZUI_FILEBROWSER
#ifdef ZUI_HTMLFOLDER
  }else if(el.tagName() == ZUI_HTMLFOLDER){
      zRes.widget = new ZHTMLFolderView(el, zRes.parent);

#endif // ZUI_HTMLFOLDER
#ifdef ZUI_FOLDERVIEW
  }else if(el.tagName() == ZUI_FOLDERVIEW){
      zRes.widget = new ZFolderView(el, zRes.parent);

#endif // ZUI_FOLDERVIEW
#ifdef ZUI_WEBBROWSER //	web browser: embeds a full WebKit browser
  }else if(el.tagName() == ZUI_WEBBROWSER){
      zRes.widget = new ZWebBrowser("www.google.com", el, zRes.parent);
//      CAST(ZWebBrowser*,zRes.widget)->show();
//      CAST(ZWebBrowser*,zRes.widget)->setLayout(ZuiUtils::getLayout(
//        el.attribute("layout", ZUI_DEFAULT_LAYOUT)));
  }
#endif // ZUI_WEBBROWSER
  return zRes;
}

Q_EXPORT_PLUGIN2(zui_extras, ZExtrasModule)
