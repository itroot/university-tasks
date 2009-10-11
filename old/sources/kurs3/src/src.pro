SOURCES += main.cpp \
 MainWindow.cpp \
 GlWidget.cpp \
 Cube3D.cpp \
 OctoCube3D.cpp \
 Simplex3D.cpp \
 Point3D.cpp
TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt \
 opengl \
 debug
TARGET = ../bin/kurs3

HEADERS += MainWindow.h \
GlWidget.h \
 Cube3D.h \
 OctoCube3D.h \
 Simplex3D.h \
 Point3D.h
QT += opengl

CONFIG -= release

