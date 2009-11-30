#include <cubant/Cubant.hpp>

#include <iostream>

using namespace std;
using namespace CubantCore;

void points() {
  cubant_t c1("/2,2,2/");
  cubant_t c2("/1,2,2/");
  cubant_t::points_t points=c1.getPoints();
  cout << "Size:" << points.size() << endl;
  for (cubant_t::points_t::iterator it=points.begin();it!=points.end();++it) {
    for (cubant_t::point_t::const_iterator jt=it->begin(); jt!=it->end();++jt) {
      cout << *jt << " ";
    }
    cout << endl;
  }
  for (int i=0;i<100000;++i) cubant_t::hausdorff_distance(c1.getPoints(), c2.getPoints());
  //cout << "HHH: " << cubant_t::hausdorff_distance(c1.getPoints(), c2.getPoints()) << endl;
}

int main() {
    points();
    std::string cubant_str="/1,1,1,1,2,0,Z/";
    cubant_t c(cubant_str);
    cout << "Was: " << cubant_str << " now: " << c.toString() << endl;
    cout << "hausdorf: " << cubant_t::hausdorf(cubant_t("/0,2,2,0/"), cubant_t("/1,2,1,1/")) << endl;
    return cubant_str!=c.toString();
}
