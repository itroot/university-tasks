#ifndef CUBANT_COMPLEX_CXX_H_
#define CUBANT_COMPLEX_CXX_H_

#include <map>
#include <vector>
#include <set>
#include <algorithm>



#include <cubant/Cubant.hpp>


using namespace CubantCore; // FIXME

struct Point3D {
  Point3D(): x(0), y(0), z(0) {}
  double x;
  double y;
  double z;
};

class CubantComplex3D {
  public:
    CubantComplex3D()
    : cubants(0)
    {
      if (!cubantsCode.empty()) {
        return; // BAD CODE =)
      }
      cubantsCode[1]=cubant_t("/0,0,0/");
      cubantsCode[2]=cubant_t("/0,0,1/");
      cubantsCode[4]=cubant_t("/0,1,0/");
      cubantsCode[8]=cubant_t("/0,1,1/");
      cubantsCode[16]=cubant_t("/1,0,0/");
      cubantsCode[32]=cubant_t("/1,0,1/");
      cubantsCode[64]=cubant_t("/1,1,0/");
      cubantsCode[128]=cubant_t("/1,1,1/");

      cubantsCode[256]=cubant_t("/0,0,2/");
      cubantsCode[512]=cubant_t("/0,1,2/");
      cubantsCode[1024]=cubant_t("/0,2,0/");
      cubantsCode[2048]=cubant_t("/0,2,1/");
      cubantsCode[4096]=cubant_t("/1,0,2/");
      cubantsCode[8192]=cubant_t("/1,1,2/");
      cubantsCode[16384]=cubant_t("/1,2,0/");
      cubantsCode[32768]=cubant_t("/1,2,1/");
      cubantsCode[65536]=cubant_t("/2,0,0/");
      cubantsCode[131072]=cubant_t("/2,0,1/");
      cubantsCode[262144]=cubant_t("/2,1,0/");
      cubantsCode[524288]=cubant_t("/2,1,1/");

      cubantsCode[1048576]=cubant_t("/0,2,2/");
      cubantsCode[2097152]=cubant_t("/1,2,2/");
      cubantsCode[4194304]=cubant_t("/2,0,2/");
      cubantsCode[8388608]=cubant_t("/2,1,2/");
      cubantsCode[16777216]=cubant_t("/2,2,0/");
      cubantsCode[33554432]=cubant_t("/2,2,1/");

      cubantsCode[67108864]=cubant_t("/2,2,2/"); // 2**27 == 134217728
      
    }
    unsigned int& getCubants() {
      return cubants;
    }
    /*
    std::vector<cubant_t> getComplexCubants() {
      std::vector<cubant_t> result;
      for (std::map<unsigned int, cubant_t>::iterator it=cubantsCode.begin();it!=cubantsCode.end(); ++it) {
        if (cubants & it->first) {
          result.push_back(it->second);
        }
      }
      return result;
    }
    */
    cubant_t::points_t getPoints() {
      cubant_t::points_t  result;
       for (std::map<unsigned int, cubant_t>::iterator it=cubantsCode.begin();it!=cubantsCode.end(); ++it) {
          if (cubants & it->first) {
            cubant_t::points_t p=it->second.getPoints();
            result.insert(p.begin(), p.end());
          }
       }
      return result;
    }
  private:
    unsigned int cubants;
    // FIXME NOT MULTITHREADED move to singleton
    static std::map<unsigned int, cubant_t> cubantsCode;
};

int distance2(const cubant_t::point_t& p1, const cubant_t::point_t& p2) {
  int result=0;
  if (p1.size()!=p2.size()) throw cubant_exception("Size do not match");
  for (size_t i=0;i<p1.size();++i) {
    result+=p1[i]*p1[i]+p2[i]*p2[i];
  }
  return result;
}

int hausdorf_distance(const cubant_t::points_t& p1, const cubant_t::points_t& p2) {
  int result=-1;
  const size_t s1=p1.size();
  const size_t s2=p2.size();

  int* array=new int[s1*s2];
  // Filling the table;
  int i=0;
  for (cubant_t::points_t::const_iterator it=p1.begin();it!=p1.end();++it,++i) {
    int j=0;
    for (cubant_t::points_t::const_iterator jt=p2.begin();jt!=p2.end();++jt,++j) {
      array[s2*i+j]=distance2(*it, *jt);
    }
  }

  //1st
  
  int r1=0;
  std::vector<int> v1(s1,0);
  for (size_t i=0;i<s1;++i) {
    v1[i]=array[s2*i];
    for (size_t j=0;j<s2;++j) {
      v1[i]=std::min(v1[i], array[s2*i+j]);
    }
  }
  
  r1=v1[0];
  for (size_t i=0;i<v1.size();++i) {
    r1=std::max(r1, v1[i]);
  }
  
  // 2nd

  int r2=0;
  std::vector<int> v2(s2,0);
  
  for (size_t j=0;j<s2;++j) {
    v2[j]=array[j];
    for (size_t i=0;i<s1;++i) {
      v2[j]=std::min(v2[j], array[s2*i+j]);
    }
  }
  
  r2=v2[0];
  for (size_t i=0;i<v2.size();++i) {
    r2=std::max(r2, v2[i]);
  }
  result=std::max(r1,r2);
  delete[] array;
  return result;
}

#endif
