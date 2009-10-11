#ifndef VISUALGRID_H_
#define VISUALGRID_H_

#include "VisualEntity.h"
#include "VisualTriangle.h"
#include "tmath/Grid3D.h"
#include <QtOpenGL>

class VisualGrid : public VisualEntity {
  public:
    VisualGrid(Grid3D* _grid):grid(_grid){

      for (unsigned int x=0;x<size_traits::SIZE;++x) {
        for (unsigned int y=0;y<size_traits::SIZE;++y) {
          for (unsigned int z=0;z<size_traits::SIZE;++z) {
            Children.push_back(new VisualPoint(2*x,2*y,2*z));
            //cout << "!!\n" << " x: " << x  << " y: " << y << " z: " << z << endl;
          }
        }
      }
      setTheyChildPolicy(true);
      setThisChildPolicy(true);
    }
    void virtual renderMe();
  private:
    Grid3D* grid;
};

#endif /*VISUALGRID_H_*/
