#include "reper.h"

Reper::
Reper(unsigned int _num, unsigned int _height, unsigned int _width)
  : num(_num)
  , height(_height)
  , width(_width)
{}

unsigned int
Reper::
getNum() {
	return num;
}
unsigned int
Reper::
getHeight() {
	return height;
}

unsigned int
Reper::
getWidth() {
	return width;
}

