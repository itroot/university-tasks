#include "SimplexModel.h"



SimplexModel::SimplexModel(const Point3D& p1,
                           const Point3D& p2,
                           const Point3D& p3,
                           const Point3D& p4) {
  vertices.push_back(p1);
  vertices.push_back(p2);
  vertices.push_back(p3);
  vertices.push_back(p4);
}

SimplexModel::~SimplexModel() {}

vector<Point3D>& SimplexModel::getVertices() {
  return vertices;
}

bool SimplexModel::containsZero() {
  return vertices[0].isZero() || vertices[1].isZero() || vertices[2].isZero() || vertices[3].isZero();
}


ostream& operator<<(ostream& out, const SimplexModel& simplexModel) {
  const size_t vertices_number=simplexModel.vertices.size();
  for (size_t i=0;i<vertices_number;++i) {
    out << simplexModel.vertices[i];
  }
  return out;
}
