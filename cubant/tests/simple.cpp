#include <cubant/Cubant.hpp>

#include <iostream>

using namespace std;
using namespace CubantCore;

void points() {
  string cubant_str="/2,2,2/";
  cubant_t c(cubant_str);
  cubant_t::points_t points=c.getPoints();
  cout << "Size:" << points.size() << endl;
  for (cubant_t::points_t::iterator it=points.begin();it!=points.end();++it) {
    for (cubant_t::point_t::const_iterator jt=it->begin(); jt!=it->end();++jt) {
      cout << *jt << " ";
    }
    cout << endl;
  }
}

int main() {
    points();
    std::string cubant_str="/1,1,1,1,2,0,Z/";
    cubant_t c(cubant_str);
    cout << "Was: " << cubant_str << " now: " << c.toString() << endl;
    cout << "hausdorf: " << cubant_t::hausdorf(cubant_t("/0,2,2,0/"), cubant_t("/1,2,1,1/")) << endl;
    return cubant_str!=c.toString();
}
