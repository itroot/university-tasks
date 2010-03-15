#include "MainWindow.h"
#include "Renderer.h"
//test
#include <set>
#include <QDebug>
#include <QTime>
#include <iostream>
#include <algorithm>
#include <fstream>
#include "visuals/VisualPoint.h"
#include "visuals/VisualLine.h"
#include "visuals/VisualTriangle.h"
#include "visuals/VisualSimplex3D.h"
#include "tmath/Cube3D.h"
#include "tmath/BitContainer.h"
#include "tmath/Matrix3D.h"
#include "tmath/Rotator3D.h"
#include "tmath/Point3D.h"
#include "tmath/OctoCube.h"
#include "tmath/Line3D.h"
#include "tmath/SimplexModel.h"
#include "Etc.h"
#include "tmath/EtalonDiags.h"
#include "ChoiceDialog.h"
#include "tmath/Facet.h"
#include "tmath/Grid3D.h"
#include "visuals/VisualGrid.h"

namespace {
  bool compareRotatedDiags(const vector<Diagonal>& lhs, const vector<Diagonal>& rhs) {
    bool result = true;
    const size_t v_size=lhs.size();
    if (v_size!=rhs.size()) {
      cerr << "Vectors lengs differs\n";
    }
    for (size_t i=0;i<v_size;++i) {
      if (!(lhs[i]==rhs[i])) { 
        result=false;
        break;
      }
    }
    return result;
  }


  vector<Facet> getFacetsFromSimplexes(vector<SimplexModel>& smpl) {
    vector<Facet> result;
    for(size_t i=0;i<smpl.size();++i) {
      vector<Point3D> cvert=smpl[i].getVertices();
      result.push_back(Facet(cvert[0],cvert[1],cvert[2]));
      result.push_back(Facet(cvert[0],cvert[1],cvert[3]));
      result.push_back(Facet(cvert[0],cvert[2],cvert[3]));
      result.push_back(Facet(cvert[1],cvert[2],cvert[3]));
    }
    return result;
  }
  vector<Facet> getUniqueFacets(const vector<Facet>& facets) {
    vector<Facet> result;
    for (size_t i=0;i<facets.size();++i) {
      int equal=0;
      for (size_t j=0;j<facets.size();++j) {
        if (facets[i]==facets[j]) ++equal;
      }
      if (1==equal) {
        result.push_back(facets[i]);
        //cout << facets[i] << endl;
      }
    }
    return result;
  }


}

// HACK procedure
namespace {
    
    Point3D getPointFromCubes(CubeValues& cubeValues) {
        unsigned int x=0;
        unsigned int y=0;
        unsigned int z=0;
        bool found=false;
        //cerr << cubeValues << endl;
        for (x=0;x<2;++x) {
            for (y=0;y<2;++y) {
                for (z=0;z<2;++z) {
                    //cerr << cubeValues.cubes[x+2*y+4*z] << endl;
                    if (0!=cubeValues.cubes[x+2*y+4*z]) {
                        found=true;
                    }
                    if (found) break;
                }
                if (found) break;
            }
            if (found) break;
        }
        if (!found) {
            throw 1;
        }
        unsigned int currentCube=cubeValues.cubes[x+2*y+4*z];
        int X=x?1:-1;
        int Y=y?1:-1;
        int Z=z?1:-1;
        cerr << "currentCube: " << currentCube << endl;
        cerr << "X: " << X << " Y: " << Y << " Z: " << Z << endl;
        int dX=0;
        int dY=0;
        int dZ=0;
        if (1==currentCube) {
            dX=-1;
        } else if (2==currentCube) {
            dY=-1;
        } else if (4==currentCube) {
            dZ=-1;
        } else if (8==currentCube) {
            dX=1;
        } else if (16==currentCube) {
            dY=1;
        } else if (32==currentCube) {
            dZ=1;
        } else throw 42;
        X+=dX;
        Y+=dY;
        Z+=dZ;
        cerr << "::X: " << X << " Y: " << Y << " Z: " << Z << endl;
        Point3D point(X,Y,Z);
        return point;
    }
    CubeValues rotateCubes(CubeValues& cubeValues, unsigned int rotationNum) {
        CubeValues result;
        Point3D point;
        point=getPointFromCubes(cubeValues);
        Rotator3D rotator3d;
        rotator3d.setCurrentRotation(rotationNum);
        rotator3d(point);
        unsigned int X=point.X();
        unsigned int Y=point.Y();
        unsigned int Z=point.Z();
        cerr << "->X: " << X << " Y: " << Y << " Z: " << Z << endl;
        
        return result;
    }
    void generateRotationMap(unsigned int internalFace,
                             unsigned int externalFace,
                             unsigned int rotationNum)
    {
        unsigned int IFbit=internalFace?1:0;
        if (internalFace) IFbit<<=(internalFace-1);
        unsigned int EFbit=externalFace?1:0;
        if (externalFace) EFbit<<=(externalFace-1);
        cerr << "// IF: " << internalFace << " bit: " << IFbit <<
                " EF: " << externalFace << " bit: " << EFbit <<
                " ROT: " << rotationNum << endl;
        ;
        OctoCube octoCube(EFbit, IFbit);
        CubeValues cubeValues=octoCube.getCubes();
        CubeValues cubeValuesR=rotateCubes(cubeValues, rotationNum);
        OctoCubeValues octoCubeR;
        octoCubeR=OctoCube::c2o(cubeValuesR);
        cerr << "e: " << octoCubeR.ext_faces << " i: " << octoCubeR.int_faces
        << endl;
    }
    void hack_procedure() {
        for (unsigned int r=0;r<48;++r) {
            for (unsigned int j=1;j<=24;++j) {
                generateRotationMap(0,j,r);
            }
            for (unsigned int i=1;i<=12;++i) {
                generateRotationMap(i,0,r);
            }
        }
    }
}

MainWindow::MainWindow() {

hack_procedure();

createWidgets();
createActions();
createMenus();
proceedRequest();

resize(800,600);
// Set aplication name (and version? =)) )
setWindowTitle(tr("TViz"));

QTime time;
qsrand(time.msec());
}

void MainWindow::proceedRequest() {
  EtalonDiags::init();
  OctoCube ocube(static_ext_faces,static_int_faces);
  CubeValues cubesValues=ocube.getCubes();
  Grid3D* grid=new Grid3D();
  //cubesValues=grid->getCubeValues(2,2,2);

  renderer->addVisual(new VisualGrid(grid));

  vector<Cube3D> cubes3D; // Кубы
  for (unsigned int i=0;i<8;++i) {
    cubes3D.push_back(Cube3D(cubesValues.cubes[i]));
    //cout << cubes3D.back();
  }
  vector<vector<Diagonal> > CubesDiagonals; // diagonals;
  for (unsigned int i=0;i<8;++i) {
    CubesDiagonals.push_back(cubes3D[i].getDiagLines());
  }
  // find good rotations
  vector<IntMatrix3D> matrixes;
  // fill matrixes;
  for (unsigned int i=0;i<8;++i) {
    IntMatrix3D matrix;
    matrix.loadIdentity();
    matrixes.push_back(matrix);
  }
  EtalonDiags::Type CubesTypes[8]={EtalonDiags::T_UNKNOWN}; // типы сиплексов
  unsigned int RotationNum[8]={0}; // номера поворотов

  for (unsigned int i=0;i<8;++i) {  // по всем кубам
    const unsigned int tr=cubes3D[i].getTr();
    Rotator3D rotator;
    EtalonDiags::Type type=EtalonDiags::T_UNKNOWN;
    unsigned int rotation_num=0;
    for (unsigned int j=0;j<Rotator3D::NUM_OF_ROTATIONS;++j) {  // по всем поворотам
      vector<Diagonal> t0602=EtalonDiags::getDiagsByType(EtalonDiags::T_0602);
      vector<Diagonal> t1331=EtalonDiags::getDiagsByType(EtalonDiags::T_1331);
      vector<Diagonal> t2060=EtalonDiags::getDiagsByType(EtalonDiags::T_2060);
      vector<Diagonal> t2222=EtalonDiags::getDiagsByType(EtalonDiags::T_2222);
      vector<Diagonal> t4004=EtalonDiags::getDiagsByType(EtalonDiags::T_4004);
      
      rotator.setCurrentRotation(j);
      rotation_num=j;

      // ===============0602
      for (unsigned int k=0;k<6;++k) {  // по диагоналям
        //cout << t0602.size()<< endl;
       rotator(t0602[k].getP1());
       rotator(t0602[k].getP2());
       //cout << t0602[k];
      }
      //cout << ">"<<Cube3D::trFromDiags(t0602) << endl;
      if (tr==Cube3D::trFromDiags(t0602)) {
        type=EtalonDiags::T_0602;
        break;
      }

      // ===============1331
      for (unsigned int k=0;k<6;++k) {  // по диагоналям
        rotator(t1331[k].getP1());
        rotator(t1331[k].getP2());
      }
      //cout << ">"<<Cube3D::trFromDiags(t1331) << endl;
      if (tr==Cube3D::trFromDiags(t1331)) {
        type=EtalonDiags::T_1331;
        break;
      }
      
      // ===============2060
      for (unsigned int k=0;k<6;++k) {  // по диагоналям
        rotator(t2060[k].getP1());
        rotator(t2060[k].getP2());
      }
      //cout << ">"<<Cube3D::trFromDiags(t2060) << endl;
      if (tr==Cube3D::trFromDiags(t2060)) {
        type=EtalonDiags::T_2060;
        break;
      }
      
      
            // ===============2222
      for (unsigned int k=0;k<6;++k) {  // по диагоналям
        rotator(t2222[k].getP1());
        rotator(t2222[k].getP2());
      }
      //cout << ">"<<Cube3D::trFromDiags(t2222) << endl;
      if (tr==Cube3D::trFromDiags(t2222)) {
        type=EtalonDiags::T_2222;
        break;
      }
      
       // ===============4004
      for (unsigned int k=0;k<6;++k) {  // по диагоналям
        rotator(t4004[k].getP1());
        rotator(t4004[k].getP2());
      }
      //cout << ">"<<Cube3D::trFromDiags(t4004) << endl;
      if (tr==Cube3D::trFromDiags(t4004)) {
        type=EtalonDiags::T_4004;
        break;
      }
    }
    if (EtalonDiags::T_UNKNOWN==type) {
      cout << "Illegal type" << endl;
      throw;
    }
    //cout << type << endl;
    CubesTypes[i]=type;
    RotationNum[i]=rotation_num;
  }  // конец по всем кубам
  
  // Теперь отрисовка (нужно повернуть симплексы)
  
  vector<vector<SimplexModel> > simplexesModels;
  
  for (unsigned int i=0;i<8;++i) {
    vector<SimplexModel> simplexesModel=EtalonDiags::getSimplexByType(CubesTypes[i]);
    // выполняем поворот
    const size_t simplexes_num=simplexesModel.size();
    Rotator3D rotator;
    rotator.setCurrentRotation(RotationNum[i]);
    for (size_t j=0;j<simplexes_num;++j) {
      rotator(simplexesModel[j].getVertices()[0]);
      rotator(simplexesModel[j].getVertices()[1]);
      rotator(simplexesModel[j].getVertices()[2]);
      rotator(simplexesModel[j].getVertices()[3]);
    }
    simplexesModels.push_back(simplexesModel);
  }
  
  // Итак, мы получили нужные симплексы. Теперь нужно их отобрать
   for (unsigned int x=0;x<=1;++x) {
     for (unsigned int y=0;y<=1;++y) {
       for (unsigned int z=0;z<=1;++z) {
         const unsigned int offset=x+2*y+4*z;
         for (size_t j=0;j<simplexesModels[offset].size();++j) {
           vector<Point3D>& vert=simplexesModels[offset][j].getVertices();
           for (size_t k=0;k<vert.size();++k) {
             if (x) vert[k].X()++; else vert[k].X()--;
             if (y) vert[k].Y()++; else vert[k].Y()--;
             if (z) vert[k].Z()++; else vert[k].Z()--;
           }
         }
       }
     }
   }


  vector <SimplexModel> usableSimplexes;
  for (size_t i=0; i<simplexesModels.size();++i) {
    for (size_t j=0; j<simplexesModels[i].size();++j) {
      if (simplexesModels[i][j].containsZero()) {
        usableSimplexes.push_back(simplexesModels[i][j]);

      }
    }
  }

  if (static_is_dual) {
    cout << endl << usableSimplexes.size() << endl;
    vector<Facet> facets;
    facets=getFacetsFromSimplexes(usableSimplexes);
    cout << endl << facets.size() << endl;
    vector<Facet> ufacets;
    ufacets=getUniqueFacets(facets);
    cout << endl << ufacets.size() << endl;
  
    for (size_t i=0;i<ufacets.size();++i) {
      renderer->addVisual(new VisualPoint(ufacets[i].getCenter()));
    }
  
    unsigned int num_of_lines=0;
    for (size_t i=0;i<ufacets.size();++i) {
      for (size_t j=0;j<i;++j) {
        if (2==numOfCommonVertices(ufacets[i],ufacets[j])) {
          renderer->addVisual(new VisualLine(ufacets[i].getCenter(),ufacets[j].getCenter()));
          ++num_of_lines;
        }
      }
    }
    cout << "Num of lines: " << num_of_lines << endl;
  }
  
  if (static_is_usial) { // not dual

    for (size_t i=0;i<usableSimplexes.size();++i) {
    renderer->addVisual(
                        new  VisualSimplex3D(
     VisualPoint(usableSimplexes[i].getVertices()[0].X(),
        usableSimplexes[i].getVertices()[0].Y(),
        usableSimplexes[i].getVertices()[0].Z()),
        VisualPoint(usableSimplexes[i].getVertices()[1].X(),
                    usableSimplexes[i].getVertices()[1].Y(),
                        usableSimplexes[i].getVertices()[1].Z()),
            VisualPoint(usableSimplexes[i].getVertices()[2].X(),
                        usableSimplexes[i].getVertices()[2].Y(),
                            usableSimplexes[i].getVertices()[2].Z()),
                VisualPoint(usableSimplexes[i].getVertices()[3].X(),
                            usableSimplexes[i].getVertices()[3].Y(),
                                usableSimplexes[i].getVertices()[3].Z())
                                            )
                       );
    }
  }
  

}

MainWindow::~MainWindow() {
  delete renderer;
}


void MainWindow::createWidgets() {
  ChoiceDialog chd;
  chd.exec();

  cout << "Run with parameters: " 
      << "Ext: " <<static_ext_faces 
      << " Int: "<< static_int_faces 
      << " isDual: " << static_is_dual
      << " isUsial: " << static_is_usial << endl;
  renderer=new Renderer(this);
  // It is for handling mouse gestures, etc.
  renderer->setFocusPolicy(Qt::StrongFocus);
  setCentralWidget(renderer);
  

  //SimplexModel smodel(Point3D(1,1,1),Point3D(1,1,1),Point3D(1,1,1),Point3D(1,1,1));
  //cout << smodel << endl;
  
  //test
  //for (int i=0;i<64;++i) {
  //vector<Diagonal> v;
  //Cube3D cube (i);
  //v=cube.getDiagLines();
  //for (int i=0; i< v.size();++i) {
  //  cout << v[i];
  //}
  //cout << "# " << i << ' '<< cube.trFromDiags(v) << " #" << endl;
  //}
  //Line3D line1(Point3D(1,1,1),Point3D(2,2,2));
  //Line3D line2(Point3D(1,1,1),Point3D(2,2,2));
  
  //cout << (line1==line2) << endl;
  
  //Cube3D cube3d(23);
/*  
  CubeValues cvalues;
  OctoCubeValues ovalues(static_ext_faces,static_int_faces);

  cout << ovalues;
  cvalues=OctoCube::o2c(ovalues);
  cout << cvalues;
  cout << OctoCube::c2o(cvalues);*/

  //cout << cube3d;
  //std::cout<<"Nuint:"<<cont.Nuint<<std::endl;
  /*//~cont;
  unsigned int *p = cont.getP();
  std::cout<<"1 "<< *p <<" 2 "<<*(p+1);
  std::cout<<std::endl;
  --cont;
  std::cout<<"1 "<< *p <<" 2 "<<*(p+1);
  std::cout<<std::endl;
 */// ~cont;

  
  /*
  std::cout<<std::endl;
  for (int j=0;j<16;++j) {
  cont.setbit(j);
  
  for (int i=0;i<16;++i) std::cout << cont.getbit(i);
  
  std::cout<<std::endl;
  }
  
  for (int j=0;j<16;++j) {
  cont.resetbit(j);
  
  for (int i=0;i<16;++i) std::cout << cont.getbit(i);
  
  std::cout<<std::endl;
  }
  */
  //Rotator3D rotator;

  /*
   * */
   //int arr1[9]={0,0,1,
   /*             0,1,0,
                1,0,0};
   int arr2[9]={0,0,1,
                0,1,0,
                1,0,0};
   Matrix3D<int> matr1(arr1);
   Matrix3D<int> matr2(arr2);
   //std::cout << matr1*matr2;
   //std::cout <<":"<< sizeof(Matrix3D<int>)<<":"<<endl;;
   Point3D point (1,1,1);
   //cout << point;
   IntMatrix3D matrix=rotator[15];
   //cout << matrix;
   //cout <<*/ //point*matrix;
   

 
   
   
  /*
  renderer->addVisual(new VisualPoint(8,8,8));
  VisualPoint p1=VisualPoint(1,1,0);
  VisualPoint p2=VisualPoint(7,8,1);
  renderer->addVisual(new VisualLine(p1,p2));
  renderer->addVisual(new VisualTriangle(
                            VisualPoint(3,4,5),
                            VisualPoint(3,7,5),
                            VisualPoint(3,4,9)
                            ));
  renderer->addVisual(new VisualSimplex3D(
    VisualPoint(10,10,10),
    VisualPoint(10,20,10),
    VisualPoint(20,10,10),
    VisualPoint(10,10,20)
    ));  
                */          
}

void MainWindow::createActions() {
	
}

void MainWindow::createMenus() {
	
}

