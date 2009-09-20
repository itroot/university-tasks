AM_CPPFLAGS = -I../include -I/usr/include/mozjs
AM_CXXFLAGS = -Wall -Wextra -Wconversion -pedantic -pthread\
              -DXP_UNIX -Wno-long-long

bin_PROGRAMS=cbshell

cbshell_SOURCES = cbshell.cpp
cbshell_LDADD = -L../src -lcubant -lmozjs

