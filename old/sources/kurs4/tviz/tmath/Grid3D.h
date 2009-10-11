#ifndef GRID3D_H_
#define GRID3D_H_
#include <vector>
#include "Etc.h"
#include "OctoCube.h"

#include <QtGlobal>

using namespace std;

struct size_traits {
  static const unsigned int SIZE=5; // >3
};

struct Slice {
  Slice() {
    for (size_t i=0;i<size_traits::SIZE;++i) {
      for (size_t j=0;j<size_traits::SIZE;++j) {
        slice[i][j]=qrand()%10;
      }
    }
  }
  unsigned int& getFacet(unsigned int n1, unsigned int n2) {
    if (n1>=size_traits::SIZE || n2>=size_traits::SIZE) {
      throw;
    }
    return slice[n1][n2];
  }
  unsigned int slice[size_traits::SIZE][size_traits::SIZE];
};

struct Grid3D {
  Slice x[size_traits::SIZE];
  Slice y[size_traits::SIZE];
  Slice z[size_traits::SIZE];
  unsigned int getCubeTr(unsigned int nx, unsigned int ny, unsigned int nz) {
    unsigned int result=0;
    if (nx-1>=size_traits::SIZE || ny-1>=size_traits::SIZE || nz-1>=size_traits::SIZE) {
      throw;
    }

    setBinaryDigit(result, 0, (x[nx]).getFacet(ny,nz));
    setBinaryDigit(result, 3, (x[nx+1]).getFacet(ny,nz));

    setBinaryDigit(result, 1, (y[ny]).getFacet(nx,nz));
    setBinaryDigit(result, 4, (y[ny+1]).getFacet(nx,nz));

    setBinaryDigit(result, 2, (z[nz]).getFacet(nx,ny));
    setBinaryDigit(result, 5, (z[nz+1]).getFacet(nx,ny));
    return result;
  }


  CubeValues getCubeValues(unsigned int nx, unsigned int ny, unsigned int nz) {
    CubeValues result;
    if (nx-2>=size_traits::SIZE || ny-2>=size_traits::SIZE || nz-2>=size_traits::SIZE) {
      throw;
    }
    if (nx<1 || ny<1 || nz<1) {
      throw;
    }
    //cout << "Hah" << endl;
    for (unsigned int ix=nx-1;ix<=nx;++ix) {
      for (unsigned int iy=ny-1;iy<=ny;++iy) {
        for (unsigned int iz=nz-1;iz<=nz;++iz) {
          result.cubes[(nx-ix)+2*(ny-iy)+4*(nz-iz)]=getCubeTr(ix,iy,iz);
          //cout << "Bah!: " << ((nx-ix)+2*(ny-iy)+4*(nz-iz)) << endl;
        }
      }
    }
    return result;
  }
  //void Render() ??
};

#endif
