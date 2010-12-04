/******************************************************************************
*    This file is part of Zee.
*
*    Zee is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    Zee is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with Zee.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#include "zextrasmodule.h"

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
      zRes.widget = new ZWebBrowser(el, zRes.parent);
//      CAST(ZWebBrowser*,zRes.widget)->show();
//      CAST(ZWebBrowser*,zRes.widget)->setLayout(ZuiUtils::getLayout(
//        el.attribute("layout", ZUI_DEFAULT_LAYOUT)));
#endif // ZUI_WEBBROWSER
#ifdef ZUI_TERMINAL
  }else if(el.tagName() == ZUI_TERMINAL){
      zRes.widget = new ZTerminal(el, zRes.parent);
#endif // ZUI_TERMINAL
  }
  return zRes;
}

Q_EXPORT_PLUGIN2(zui_extras, ZExtrasModule)
