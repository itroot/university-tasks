#ifndef OCTOCUBE_H_
#define OCTOCUBE_H_

#include <iostream>

using namespace std;

struct OctoCubeValues {
  OctoCubeValues(unsigned int _ext_faces=0, unsigned int _int_faces=0):
      ext_faces(_ext_faces), int_faces(_int_faces) {}
  unsigned int ext_faces;
  unsigned int int_faces;
};

struct CubeValues {
  CubeValues() {
    for (unsigned int i=0;i<8;++i) {
      cubes[i]=0;
    }
  }
  unsigned int cubes[8];
};


ostream& operator<<(ostream& out, const CubeValues& cvalues);
ostream& operator<<(ostream& out, const OctoCubeValues& ovalues);


class OctoCube {
  public:
    OctoCube(unsigned int _ext_faces=0, unsigned int _int_faces=0);
    ~OctoCube();
    static CubeValues o2c(const OctoCubeValues& ovalues);
    static OctoCubeValues c2o(const CubeValues& cvalues);
    const CubeValues& getCubes()const;
    const OctoCubeValues& getOctoCubes()const;
    bool isGood();
  private:
    OctoCubeValues ovalues;
    CubeValues cvalues;
};

#endif
