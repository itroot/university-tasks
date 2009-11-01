AM_CPPFLAGS = -I../include -I/usr/include/mozjs -I/home/itroot/Desktop/dev/prefix/include/js
AM_CXXFLAGS = -Wall -Wextra -Wconversion -pedantic -pthread\
              -DXP_UNIX -Wno-long-long

bin_PROGRAMS=cbshell

cbshell_SOURCES = cbshell.cpp
cbshell_LDADD = -L../src -L/home/itroot/Desktop/dev/prefix/lib -lcubant -lmozjs

