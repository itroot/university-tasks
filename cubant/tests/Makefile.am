AM_CPPFLAGS = -I../include
AM_CXXFLAGS = -Wall -Wextra -Wconversion -pedantic -pthread

check_PROGRAMS=simple

simple_SOURCES = simple.cpp
simple_LDADD = -L../src -lcubant

TESTS=$(check_PROGRAMS)
