#include "Line3D.h"


Line3D::Line3D(Point3D _p1, Point3D _p2) 
  :p1(_p1),p2(_p2){}

Line3D::~Line3D() {}

bool Line3D::operator==(const Line3D& rhs) const {
  return (p1==rhs.p1 && p2==rhs.p2) || (p1==rhs.p2 && p2==rhs.p1);
}

bool Line3D::operator<(const Line3D& rhs) const {
  if (this->p1<rhs.p1) return true;
  if (this->p1>rhs.p1) return false;
  if (this->p2<rhs.p2) return true;
  if (this->p2>rhs.p2) return false;
  return false;
}

Point3D& Line3D::getP1() {
  return p1;
}

Point3D& Line3D::getP2() {
  return p2;
}

const Point3D& Line3D::getP1() const {
  return p1;
}

const Point3D& Line3D::getP2() const {
  return p2;
}

ostream& operator<<(ostream& out, const Line3D& line) {
  return out<< line.p1 << line.p2 << endl;
}

