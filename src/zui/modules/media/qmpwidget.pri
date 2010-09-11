#
#  qmpwidget - A Qt widget for embedding MPlayer
#  Copyright (C) 2010 by Jonas Gehring
#

HEADERS += \
	qmpwidget/qmpwidget.h

SOURCES += \
	qmpwidget/qmpwidget.cpp

!win32:pipemode: {
DEFINES += QMP_USE_YUVPIPE
HEADERS += qmpwidget/qmpyuvreader.h
}
