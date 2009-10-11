#include "Point3D.h"

Point3D::Point3D() {
  x=0;
  y=0;
  z=0;
}

Point3D::Point3D(int in_x, int in_y, int in_z) {
  x=in_x;
  y=in_y;
  z=in_z; 
}

Point3D::~Point3D() {
  
}

int Point3D::const_elem(unsigned int num) const {
  switch (num) {
    case 0: return x; break; 
    case 1: return y; break;
    case 2: return z; break;
    default: throw; break;
  }
}


int& Point3D::elem(unsigned int num) {
  switch (num) {
    case 0: return x; break; 
    case 1: return y; break;
    case 2: return z; break;
    default: throw; break;
  }
}

bool Point3D::operator<(const Point3D& rhs) const {
  if (this->x < rhs.x) return true;
  if (this->x > rhs.x) return false; 
  if (this->y < rhs.y) return true;
  if (this->y > rhs.y) return false;
  if (this->z < rhs.z) return true;
  if (this->z > rhs.z) return false;
  return false;
}

bool Point3D::operator>(const Point3D& rhs) const {
  if (this->x > rhs.x) return true;
  if (this->x < rhs.x) return false; 
  if (this->y > rhs.y) return true;
  if (this->y < rhs.y) return false;
  if (this->z > rhs.z) return true;
  if (this->z < rhs.z) return false;
  return false;
}


bool Point3D::operator==(const Point3D& rhs) const {
  return (this->x==rhs.x && this->y==rhs.y && this->z==rhs.z);
}


bool Point3D::operator!=(const Point3D& rhs) const {
  return (this->x!=rhs.x || this->y!=rhs.y || this->z!=rhs.z);
}

Point3D Point3D::operator+(const Point3D& rhs) const {
  Point3D result;
  result.x=this->x+rhs.x;
  result.y=this->y+rhs.y;
  result.z=this->z+rhs.z;
  return result;
}


ostream& operator<<(ostream& out, const Point3D& point) {
  return out<<"{"<<point.const_elem(0)<<","
                 <<point.const_elem(1)<<","
                 <<point.const_elem(2)<<"}"; 
}

int Point3D::X() const {
  return x;
}

int Point3D::Y() const {
  return y;
}

int Point3D::Z() const {
  return z;
}

int& Point3D::X() {
  return x;
}

int& Point3D::Y() {
  return y;
}

int& Point3D::Z() {
  return z;
}

bool Point3D::isZero() {
  return (0==x && 0==y && 0==z);
}


