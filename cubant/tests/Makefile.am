AM_CPPFLAGS = -I../include
AM_CXXFLAGS = -Wall -Wextra -Wconversion -pedantic -pthread

check_PROGRAMS=simple intersect

simple_SOURCES = simple.cpp
simple_LDADD = -L../src -lcubant

intersect_SOURCES = intersect.cpp
intersect_LDADD = -L../src -lcubant

TESTS=$(check_PROGRAMS)
