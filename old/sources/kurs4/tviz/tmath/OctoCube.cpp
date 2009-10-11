#include "OctoCube.h"
#include "Etc.h"
#include <iostream>
#include "Cube3D.h"
using namespace std;



OctoCube::OctoCube(unsigned int _ext_faces, unsigned int _int_faces) :
 ovalues(_ext_faces,_int_faces) {
  cvalues=o2c(ovalues);
}


OctoCube::~OctoCube(){}

CubeValues OctoCube::o2c(const OctoCubeValues& ovalues) {
  CubeValues cvalues;
  const unsigned int& externalFaces=ovalues.ext_faces;
  const unsigned int& internalFaces=ovalues.int_faces;
    // x y z - координаты куба в октокубе.
  for (int x=0;x<=1;++x) {
    for (int y=0;y<=1;++y) {
      for (int z=0;z<=1;++z) {
        int diags[6]; // временное решение.
        // Внешние грани
        diags[3*x]=getBinaryDigit(externalFaces,12*x+2*z+y);
        diags[3*y+1]=getBinaryDigit(externalFaces,12*y+4+2*z+x);
        diags[3*z+2]=getBinaryDigit(externalFaces,12*z+8+2*y+x);
        // Внутренние грани
        diags[3*(1-x)]=getBinaryDigit(internalFaces,2*z+y);
        diags[3*(1-y)+1]=getBinaryDigit(internalFaces,4+2*z+x);
        diags[3*(1-z)+2]=getBinaryDigit(internalFaces,8+2*y+x);
        unsigned int tr=diags[0]+2*diags[1]+4*diags[2]+8*diags[3]+16*diags[4]+32*diags[5];
        cvalues.cubes[x+2*y+4*z]=tr; // Это важно, в каком пордяке. X изменяется чаще.
      }
    }
  }
  return cvalues;
}

OctoCubeValues OctoCube::c2o(const CubeValues& cvalues) {
  OctoCubeValues ovalues;
  unsigned int& externalFaces=ovalues.ext_faces;
  unsigned int& internalFaces=ovalues.int_faces;
  for (int x=0;x<=1;++x) {
    for (int y=0;y<=1;++y) {
      for (int z=0;z<=1;++z) {
        unsigned int offset=x+2*y+4*z;
        //cout << '#' << offset << endl;
        // Внешние грани.
        //cout << ovalues << endl;
        setBinaryDigit(externalFaces,
                         12*x+2*z+y,
                         getBinaryDigit(cvalues.cubes[offset],
                             3*x)
                        );
        //cout << ovalues << endl;
        setBinaryDigit(externalFaces,
                        12*y+4+2*z+x,
                         getBinaryDigit(cvalues.cubes[offset],
                             3*y+1)
                        );
        //cout << ovalues << endl;
        setBinaryDigit(externalFaces,
                        12*z+8+2*y+x,
                         getBinaryDigit(cvalues.cubes[offset],
                             3*z+2)
                        );
        //cout << ovalues << endl;
        setBinaryDigit(internalFaces,
                         2*z+y,
                         getBinaryDigit(cvalues.cubes[offset],
                             3*(1-x))
                        );
       // cout << ovalues << endl;
        setBinaryDigit(internalFaces,
                         4+2*z+x,
                         getBinaryDigit(cvalues.cubes[offset],
                             3*(1-y)+1)
                        );
        //cout << ovalues << endl;
        setBinaryDigit(internalFaces,
                         8+2*y+x,
                         getBinaryDigit(cvalues.cubes[offset],
                             3*(1-z)+2)
                        );
        //cout << ovalues << endl;
      }
    }
  }
  return ovalues;
}

ostream& operator<<(ostream& out, const CubeValues& cvalues) {
  for (int x=0;x<=1;++x) {
    for (int y=0;y<=1;++y) {
      for (int z=0;z<=1;++z) {
        out << cvalues.cubes[x+2*y+4*z] << ' ' ;
      }
    }
  }
  out << endl;
  return out;
}

bool OctoCube::isGood() {
  bool result=true;
  for (unsigned int i=0;i<8;++i) {
    Cube3D cube(cvalues.cubes[i]);
    if (!cube.isGood()) {
      result=false;
      break;
    }
  }
  return result;
}

ostream& operator<<(ostream& out, const OctoCubeValues& ovalues) {
  out << ovalues.ext_faces << ' ' << ovalues.int_faces;
  out << endl;
  return out;
}

const CubeValues& OctoCube::getCubes() const {
  return cvalues;
}

const OctoCubeValues& OctoCube::getOctoCubes() const {
  return ovalues;
}




