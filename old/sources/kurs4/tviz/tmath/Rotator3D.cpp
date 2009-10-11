#include "Rotator3D.h"

set<IntMatrix3D> Rotator3D::set_rotations;
vector<IntMatrix3D> Rotator3D::vector_rotations;

Rotator3D::Rotator3D() {
  currentRotation=0;
  if (NUM_OF_ROTATIONS!=set_rotations.size()) generateRotations();
}

Rotator3D::~Rotator3D() {
}

void Rotator3D::generateRotations() {
  set<IntMatrix3D> set1;
  set<IntMatrix3D> set2;
  int a1[9]={1,0,0, // I
              0,1,0,
              0,0,1};
  int a2[9]={1,0,0, // X
              0,0,-1,     
              0,1,0};
  int a3[9]={0,0,1, // Y
              0,1,0,     
             -1,0,0};
  int a4[9]={0,-1,0, // Z
              1,0,0,     
              0,0,1};
              
  int a5[9]={-1,0,0, // !X
              0,1,0,     
              0,0,1};
  
   
  set1.insert(IntMatrix3D(a1));
  set1.insert(IntMatrix3D(a2));
  set1.insert(IntMatrix3D(a3));
  set1.insert(IntMatrix3D(a4));
  set1.insert(IntMatrix3D(a5));
   
  set2=set1;
  while (true) {
    set<IntMatrix3D>::const_iterator p=set1.begin();
    while (p!=set1.end()) {
      set<IntMatrix3D>::const_iterator q=set1.begin();
      while (q!=set1.end()) {
        set2.insert((*p)*(*q));
        q++;
      }
        p++;
    }
    if(set1.size()==set2.size()) break; 
    set1.clear();
    set1=set2;
  }
  set_rotations=set1;
  set<IntMatrix3D>::const_iterator p=set_rotations.begin();
  while (p!=set_rotations.end()) vector_rotations.push_back(*p++);
}

const IntMatrix3D& Rotator3D::operator[](unsigned int num) const {
  if (num>=NUM_OF_ROTATIONS) throw;
  return vector_rotations[num];
}

void Rotator3D::setCurrentRotation(unsigned int num) {
  if (num<NUM_OF_ROTATIONS) 
    currentRotation=num;
  else
    throw;
}

unsigned int Rotator3D::getCurrentRotation() const {
  return currentRotation;
}

void Rotator3D::operator()(Point3D& point) const {
  point=vector_rotations[currentRotation]*point;
}

/*
void Rotator3D::operator()(SimplexModel& sm) const {
  sm[0]=vector_rotations[currentRotation]*sm[0];
  sm[1]=vector_rotations[currentRotation]*sm[1];
  sm[2]=vector_rotations[currentRotation]*sm[2];
  sm[3]=vector_rotations[currentRotation]*sm[3];
}
*/


