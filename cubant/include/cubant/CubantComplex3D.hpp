#ifndef CUBANT_COMPLEX_CXX_H_
#define CUBANT_COMPLEX_CXX_H_

#include <map>
#include <vector>
#include <set>

#include <cubant/Cubant.hpp>


using namespace CubantCore; // FIXME


class CubantComplex3D {
  public:
    CubantComplex3D()
    : cubants(0)
    {
      if (!cubantsCode.empty()) {
        return; // BAD CODE =)
      }
      cubantsCode[0]=cubant_t("/0,0,0/");
      cubantsCode[1]=cubant_t("/0,0,1/");
      cubantsCode[2]=cubant_t("/0,1,0/");
      cubantsCode[4]=cubant_t("/0,1,1/");
      cubantsCode[8]=cubant_t("/1,0,0/");
      cubantsCode[16]=cubant_t("/1,0,1/");
      cubantsCode[32]=cubant_t("/1,1,0/");
      cubantsCode[64]=cubant_t("/1,1,1/");

      cubantsCode[128]=cubant_t("/0,0,2/");
      cubantsCode[256]=cubant_t("/0,1,2/");
      cubantsCode[512]=cubant_t("/0,2,0/");
      cubantsCode[1024]=cubant_t("/0,2,1/");
      cubantsCode[2048]=cubant_t("/1,0,2/");
      cubantsCode[4096]=cubant_t("/1,1,2/");
      cubantsCode[8192]=cubant_t("/1,2,0/");
      cubantsCode[16384]=cubant_t("/1,2,1/");
      cubantsCode[32768]=cubant_t("/2,0,0/");
      cubantsCode[65536]=cubant_t("/2,0,1/");
      cubantsCode[131072]=cubant_t("/2,1,0/");
      cubantsCode[262144]=cubant_t("/2,1,1/");

      cubantsCode[524288]=cubant_t("/0,2,2/");
      cubantsCode[1048576]=cubant_t("/1,2,2/");
      cubantsCode[2097152]=cubant_t("/2,0,2/");
      cubantsCode[4194304]=cubant_t("/2,1,2/");
      cubantsCode[8388608]=cubant_t("/2,2,0/");
      cubantsCode[16777216]=cubant_t("/2,2,1/");

      cubantsCode[33554432]=cubant_t("/2,2,2/");
      
    }
    unsigned int& getCubants() {
      return cubants;
    }
    std::vector<cubant_t> getComplexCubants() {
      std::vector<cubant_t> result;
      for (std::map<unsigned int, cubant_t>::iterator it=cubantsCode.begin();it!=cubantsCode.end(); ++it) {
        if (cubants & it->first) {
          result.push_back(it->second);
        }
      }
      return result;
    }
    std::set<Point3D> getPoints() {
      std::set<Point3D> result;
      
      return result;
    }
  private:
    unsigned int cubants;
    // FIXME NOT MULTITHREADED move to singleton
    static std::map<unsigned int, cubant_t> cubantsCode;
};

#endif
