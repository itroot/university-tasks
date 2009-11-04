#ifndef REPER_H
#define REPER_H

#include <vector>
#include <utility>

class Reper {
  public:
    Reper(unsigned int _num, unsigned int _height=20, unsigned int _width=50);
		unsigned int getNum();
		unsigned int getHeight();
		unsigned int getWidth();
    // virtual ??? 
    int getVectorProjection(unsigned int vectorNum, unsigned int coord);
  private:
		typedef std::pair<int, int> ReperVector;
		typedef std::vector<ReperVector> ReperVectors;
		unsigned int num;
    unsigned int height;
    unsigned int width;
		ReperVectors vectors;
};

#endif
