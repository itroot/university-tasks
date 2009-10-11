#ifndef CUBE3D_H_
#define CUBE3D_H_

#include "BitContainer.h"
#include "Line3D.h"
#include <iostream>
#include <vector>

using namespace std;

// Axis-aligned cube 3D
class Cube3D {
  public:
    static const unsigned int NUM_OF_DIAGS=6;
    static const unsigned int NUM_OF_TR=64; // 2^NUM_OF_DIAGS;
    typedef BitContainer<NUM_OF_DIAGS>  DiagsType;
    enum TypeOfTriangulation {
      T_0440, // "Bad" type, all others are good.
      T_0602, 
      T_1331,
      T_2060,
      T_2222,
      T_4004,
    };

  explicit Cube3D(unsigned int tr=0);
  ~Cube3D();
    // Set trianguliation type.
    inline void setTr(unsigned int diags);
    unsigned int getTr()const;
    vector<Diagonal> getDiagLines();
    static void bitFromDiag(const Diagonal& diag, unsigned int& bitnum, unsigned int& value);
    static unsigned int trFromDiags(const vector<Diagonal>& v);
    bool isGood();
    friend ostream& operator<<(ostream& os, const Cube3D& cube);
  private:

    /*! 0 0 z=1 y=1 x=1 z=0 y=0 x=0
    *   биты означают ориентацию диагоналей в каждой из плоскостей
    *   1- направлена в "большую сторону" 
    *     (разница модулей сумм координат противоположных вершин максимальна по модулю)
    *   0- направлена в "меньшую сторону" 
    *     (разница модулей сумм координат противоположных вершин минимальна по модулю)
    */
    
    DiagsType Diags; // Diagonals.
    int vertexPower[2][2][2];
    int typeofTr[4];
};

//ostream& operator<<(ostream& os, Cube3D& cube);

#endif /*CUBE3D_H_*/
