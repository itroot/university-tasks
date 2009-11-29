#ifndef REPER_H
#define REPER_H

#include <vector>
#include <utility>

struct Coords3D {
  Coords3D(int _x=0, int _y=0, int _z=0): x(_x), y(_y), z(_z) {}
  int x;
  int y;
  int z;
};

class Reper {
  public:
    Reper(unsigned int _num, unsigned int _height=60, unsigned int _width=30);
		unsigned int getNum();
		unsigned int getHeight();
		unsigned int getWidth();
    // virtual ??? 
    int getVectorProjection(unsigned int vectorNum, unsigned int coord);
    int getVectorProjection3D(unsigned int vectorNum, unsigned int coord);
  private:
    static const double COEFF_3D=2.0;
		typedef std::pair<int, int> ReperVector;
		typedef std::vector<ReperVector> ReperVectors;
    typedef std::vector<Coords3D> Reper3DVectors;
		unsigned int num;
    unsigned int height;
    unsigned int width;
		ReperVectors vectors;
    Reper3DVectors vectors3d;
};

#endif
