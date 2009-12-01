#include <cubant/Cubant.hpp>
#include <cubant/CubantComplex3D.hpp>

#include <iostream>

#include <stdlib.h>

using namespace std;
using namespace CubantCore;

void points() {
  //cubant_t c1("/2,2,2/");
  //cubant_t c2("/1,2,2/");
  //cubant_t::points_t points=c1.getPoints();
  //cout << "Size:" << points.size() << endl;
  /*
  for (cubant_t::points_t::iterator it=points.begin();it!=points.end();++it) {
    for (cubant_t::point_t::const_iterator jt=it->begin(); jt!=it->end();++jt) {
      cout << *jt << " ";
    }
    cout << endl;
  }
  */
  //for (int i=0;i<10000;++i) cubant_t::hausdorff_distance(c1.getPoints(), c2.getPoints());
  //cout << "HHH: " << cubant_t::hausdorff_distance(c1.getPoints(), c2.getPoints()) << endl;
  CubantComplex3D c3d;
  c3d.getCubants()=256;
  cubant_t::points_t points=c3d.getPoints();
  for (cubant_t::points_t::iterator it=points.begin();it!=points.end();++it) {
    for (cubant_t::point_t::const_iterator jt=it->begin(); jt!=it->end();++jt) {
      cout << *jt << " ";
    }
    cout << endl;
  }
}

template <class Map>
void printMap(const Map& map) {
  for (typename Map::const_iterator it=map.begin();it!=map.end();++it) {
    std::cerr << it->first << ":" << it->second << " ";
  }
  std::cerr << std::endl;
}

void do_test() {
  std::map<int, long int> result;
  const unsigned int increment=256;
  CubantComplex3D cc1;
  CubantComplex3D cc2;
  int every100k=0;
  for (unsigned int i=increment; i<134217728; i+=increment) {
    for (unsigned int j=increment; j<=i; j+=increment) {
      cc1.getCubants()=i;
      cc2.getCubants()=j;
      int d=hausdorf_distance(cc1.getPoints(), cc2.getPoints());
      if (result.find(d)==result.end()) {
        result[d]=1;
      } else {
        ++result[d];
      }
      ++every100k;
      if (0==every100k%100000) {
        printMap(result);
        every100k=0;
      }
    }
  }
}

void tmp() {
  CubantComplex3D cc1;
  CubantComplex3D cc2;
  cc1.getCubants()=1;
  cc2.getCubants()=128;
  std::cerr << "HAUSDORF: " << hausdorf_distance(cc1.getPoints(), cc2.getPoints()) << std::endl;
}

int main() {
    //points();
    /*
    std::string cubant_str="/1,1,1,1,2,0,Z/";
    cubant_t c(cubant_str);
    cout << "Was: " << cubant_str << " now: " << c.toString() << endl;
    cout << "hausdorf: " << cubant_t::hausdorf(cubant_t("/0,2,2,0/"), cubant_t("/1,2,1,1/")) << endl;
    return cubant_str!=c.toString();
    */
    do_test();
    //tmp();
    return 0;
}
