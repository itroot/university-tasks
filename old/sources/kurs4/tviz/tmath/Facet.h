#ifndef FACET_H_
#define FACET_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include "Point3D.h"
#include <visuals/VisualPoint.h>

using namespace std;

class Facet {
  public:
    Facet(vector<Point3D> init): vertices(init) {
      sort(vertices.begin(),vertices.end());
    }
    Facet(Point3D p1, Point3D p2, Point3D p3) {
      vertices.push_back(p1);
      vertices.push_back(p2);
      vertices.push_back(p3);
      sort(vertices.begin(),vertices.end());
    }
    ~Facet(){};
    VisualPoint getCenter();
    bool operator==(const Facet& other)const;
    friend ostream& operator<<(ostream& out, const Facet& facet);
    friend unsigned numOfCommonVertices(const Facet first, const Facet second);
  private:
    vector<Point3D> vertices;
};

#endif /*FACET_H_*/
