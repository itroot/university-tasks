#ifndef SIMPLEXMODEL_H_
#define SIMPLEXMODEL_H_

#include "Point3D.h"

#include <vector>

using namespace std;

class SimplexModel {
  public:
    SimplexModel(const Point3D& p1,
                 const Point3D& p2,
                 const Point3D& p3,
                 const Point3D& p4);
   friend ostream& operator<<(ostream& out, const SimplexModel& simplexModel);
   bool containsZero();
   vector<Point3D>& getVertices();// bad;
  ~SimplexModel();
  private:
    vector<Point3D> vertices;
};

#endif /*SIMPLEXMODEL_H_*/
