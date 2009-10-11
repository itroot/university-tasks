#include "Facet.h"

VisualPoint Facet::getCenter() {
  Point3D sum;
  for (size_t i=0;i<vertices.size();++i) {
    sum=sum+vertices[i];
  }
  double x=sum.X()/static_cast<double>(vertices.size());
  double y=sum.Y()/static_cast<double>(vertices.size());
  double z=sum.Z()/static_cast<double>(vertices.size());
  VisualPoint result(x,y,z);
  return result;
}

bool Facet::operator==(const Facet& other) const {
  if (other.vertices.size()!=this->vertices.size()) return false;
  for (size_t i=0;i<vertices.size();++i) {
    if (vertices[i]!=other.vertices[i]) return false;
  }
  return true;
}

ostream& operator<<(ostream& out, const Facet& facet) {
  out << "Facet : " ;
  for (size_t i=0;i<facet.vertices.size();++i) {
    out << facet.vertices[i] << ' ';
  }
  return out;
}

unsigned int numOfCommonVertices(const Facet first, const Facet second) {
  unsigned int result=0;
  for (size_t i=0;i<first.vertices.size();++i) {
    if (std::find(second.vertices.begin(),second.vertices.end(),first.vertices[i])!=second.vertices.end()) {
      ++result;
    }
  }
  return result;
}
