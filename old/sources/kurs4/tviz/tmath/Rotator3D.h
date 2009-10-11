#ifndef ROTATOR3D_H_
#define ROTATOR3D_H_

#include "Matrix3D.h"
#include "SimplexModel.h"
#include <set>
#include <vector>
using namespace std;

class Rotator3D {
  public:
  	Rotator3D();
  	~Rotator3D();
    const IntMatrix3D& operator[](unsigned int num)const;
    void setCurrentRotation(unsigned int num);
    unsigned int getCurrentRotation()const;
    void operator()(Point3D& point)const; 
    //void operator()(SimplexModel& sm)const;
    static const unsigned int NUM_OF_ROTATIONS=48;
  private:
    unsigned int currentRotation;
    static set<IntMatrix3D> set_rotations; // Here we store all 48 
    static vector<IntMatrix3D> vector_rotations; // matrices 
    static void generateRotations();
};


#endif /*ROTATOR3D_H_*/
