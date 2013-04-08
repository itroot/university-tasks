SOURCES += main.cpp \
 dspMainWindow.cpp \
 dspSound.cpp \
 FftWrapper.cpp \
 dspSpectrogram.cpp \
 dspFftData.cpp
TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt
TARGET = ../bin/task5

HEADERS += dspMainWindow.h \
dspSound.h \
 FftWrapper.h \
 dspSpectrogram.h \
 dspFftData.h

