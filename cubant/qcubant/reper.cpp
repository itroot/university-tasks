#include "reper.h"

#include <stdexcept>

Reper::
Reper(unsigned int _num, unsigned int _height, unsigned int _width)
  : num(_num)
  , height(_height)
  , width(_width)
{
    for (size_t i=0; i<num; ++i) {
        vectors.push_back(std::make_pair(height*(i-4), -width));
    }
}

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

int
Reper::
getVectorProjection(unsigned int vectorNum, unsigned int coord) {
  if (0==coord) {
    return vectors[vectorNum].first;
  } else if (1==coord) {
    return vectors[vectorNum].second;
  };
  throw std::out_of_range("No such vector dimension");
}

