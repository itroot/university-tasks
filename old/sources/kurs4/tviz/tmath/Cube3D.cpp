#include "Cube3D.h"
#include "Etc.h"
#include <algorithm>

Cube3D::Cube3D(unsigned int tr)  {
  setTr(tr%NUM_OF_TR);
}

Cube3D::~Cube3D() {
}

void Cube3D::setTr(unsigned int diags) {
  Diags=DiagsType(diags);
  // Clearing vertex powers
  for (int i=0;i<2;++i)
    for (int j=0;j<2;++j)
      for (int k=0;k<2;++k)
        vertexPower[i][j][k]=0;
  // Clear Type vector
  for (int i=0;i<4;++i) typeofTr[i]=0;      
  // Calculating vertex powers;
  ++vertexPower[0][Diags.getbit(0)][1];
  ++vertexPower[0][1-Diags.getbit(0)][0];
  ++vertexPower[1][Diags.getbit(3)][1];
  ++vertexPower[1][1-Diags.getbit(3)][0];
  
  ++vertexPower[Diags.getbit(1)][0][1];
  ++vertexPower[1-Diags.getbit(1)][0][0];
  ++vertexPower[Diags.getbit(4)][1][1];
  ++vertexPower[1-Diags.getbit(4)][1][0];
  
  ++vertexPower[Diags.getbit(2)][1][0];
  ++vertexPower[1-Diags.getbit(2)][0][0];
  ++vertexPower[Diags.getbit(5)][1][1];
  ++vertexPower[1-Diags.getbit(5)][0][1];
  // Calculating type of triangulation
  for (int i=0;i<2;++i)
    for (int j=0;j<2;++j)
      for (int k=0;k<2;++k)
        ++typeofTr[vertexPower[i][j][k]];
} 

unsigned int Cube3D::getTr() const {
  return Diags.getUint();
}

vector<Diagonal> Cube3D::getDiagLines() {
  DiagsType& tr=Diags;
  vector<Diagonal> result;
  if (1==tr.getbit(0)) {
    result.push_back(Line3D(Point3D(-1,-1,-1),Point3D(-1,1,1)));
  } else {
    result.push_back(Line3D(Point3D(-1,-1,1),Point3D(-1,1,-1)));
  }
  if (1==tr.getbit(1)) {
    result.push_back(Line3D(Point3D(-1,-1,-1),Point3D(1,-1,1)));
  } else {
    result.push_back(Line3D(Point3D(-1,-1,1),Point3D(1,-1,-1)));
  }
  if (1==tr.getbit(2)) {
    result.push_back(Line3D(Point3D(-1,-1,-1),Point3D(1,1,-1)));
  } else {
    result.push_back(Line3D(Point3D(-1,1,-1),Point3D(1,-1,-1)));
  }
  if (1==tr.getbit(3)) {
    result.push_back(Line3D(Point3D(1,1,1),Point3D(1,-1,-1)));
  } else {
    result.push_back(Line3D(Point3D(1,-1,1),Point3D(1,1,-1)));
  }
  if (1==tr.getbit(4)) {
    result.push_back(Line3D(Point3D(1,1,1),Point3D(-1,1,-1)));
  } else {
    result.push_back(Line3D(Point3D(-1,1,1),Point3D(1,1,-1)));
  }
  if (1==tr.getbit(5)) {
    result.push_back(Line3D(Point3D(1,1,1),Point3D(-1,-1,1)));
  } else {
    result.push_back(Line3D(Point3D(-1,1,1),Point3D(1,-1,1)));
  }
  sort(result.begin(),result.end());
  return result;
}

void Cube3D::bitFromDiag(const Diagonal& diag, unsigned int& bitnum, unsigned int& value) {
  bitnum=0;
  value=0;
  Point3D p1=diag.getP1();
  Point3D p2=diag.getP2();
  int p1_sum=abs(p1.X()+p1.Y()+p1.Z());
  int p2_sum=abs(p2.X()+p2.Y()+p2.Z());
  unsigned int sum=abs(p2_sum-p1_sum);
  if (0==sum) value=0; 
  else if (2==sum) value=1; 
  else cerr << "Error: strange sum in bitFromDiag\n";
  if (p1.X()==p2.X() && p1.X()==-1) bitnum=0; 
  if (p1.Y()==p2.Y() && p1.Y()==-1) bitnum=1;
  if (p1.Z()==p2.Z() && p1.Z()==-1) bitnum=2;
  if (p1.X()==p2.X() && p1.X()==1) bitnum=3;
  if (p1.Y()==p2.Y() && p1.Y()==1) bitnum=4;
  if (p1.Z()==p2.Z() && p1.Z()==1) bitnum=5;
}

unsigned int Cube3D::trFromDiags(const vector<Diagonal>& v) {
  if (v.size()!=6) {
    cerr << "Not 6 diagonals in vector.\n";
    throw;
  }
  unsigned int result=0;
  for (unsigned int i=0;i<6;++i) {
    unsigned int bitnum=0;
    unsigned int value=0;
    bitFromDiag(v[i],bitnum,value);
    //cout << "Bitnum: " << bitnum << "Value: " << value << endl;
    setBinaryDigit(result,bitnum,value);
    //cout << result << endl;
  }
  return result;
}

bool Cube3D::isGood() {
  if (0==typeofTr[0] &&
      4==typeofTr[1] &&
      4==typeofTr[2] &&
      0==typeofTr[3]) {
    return false;
  }
  else {
    return true;
  }
}

ostream& operator<<(ostream& os, const Cube3D& cube) {
  os << endl << "*** Cube3D ***" << endl;
  os << "typeofTr:" << 
  cube.typeofTr[0]<<cube.typeofTr[1]<<cube.typeofTr[2]<<cube.typeofTr[3]<<endl; 
  os<<"tr_num:"<<cube.getTr()<<endl;
  os<<"tr_bits:"<<cube.Diags<<endl;
  return os; 
}
