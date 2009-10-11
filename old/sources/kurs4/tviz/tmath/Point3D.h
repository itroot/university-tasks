#ifndef POINT3D_H_
#define POINT3D_H_

#include <iostream>
using namespace std;

class Point3D {
  public:
	  Point3D();
    Point3D(int in_x, int in_y, int in_z);
	  ~Point3D();
    int const_elem(unsigned int num)const;
    int& elem(unsigned int num);
    bool operator<(const Point3D& rhs)const;
    bool operator>(const Point3D& rhs)const;
    bool operator==(const Point3D& rhs)const;
    bool operator!=(const Point3D& rhs)const;
    Point3D operator+(const Point3D& rhs)const;
    bool isZero();
    int X() const;
    int Y() const;
    int Z() const;
    int& X();
    int& Y();
    int& Z();
    friend ostream& operator<<(ostream& out, const Point3D& point);
  private:
    int x;
    int y;
    int z;
};


#endif /*POINT3D_H_*/
