#ifndef LINE3D_H_
#define LINE3D_H_

#include "Point3D.h"

class Line3D {
  public:
  Line3D(Point3D _p1, Point3D _p2);
  ~Line3D();
  bool operator==(const Line3D& rhs) const;
  bool operator<(const Line3D& rhs)const;
  Point3D& getP1();
  Point3D& getP2();
  const Point3D& getP1()const;
  const Point3D& getP2()const;
  friend ostream& operator<<(ostream& out, const Line3D& line);
  private:
    Point3D p1;
    Point3D p2;
};

typedef Line3D Diagonal;

#endif
