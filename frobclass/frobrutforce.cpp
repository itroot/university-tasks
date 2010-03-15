#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

template<unsigned int val, unsigned int power>
struct InPower {
    enum {
        result=val*InPower<val, power-1>::result
    };
};

template<unsigned int val>
struct InPower<val, 0> {
    enum {
        result=1
    };
};

class OCubeIterator {
    public:
        OCubeIterator()
        : external_facets(0)
        , internal_facets(0)
        {}
        OCubeIterator(unsigned int ifc, unsigned int efc)
        : external_facets(efc)
        , internal_facets(ifc)
        {}
        void operator++() {
            if (IFACETS_MAX==internal_facets) {
                if (EFACETS_MAX==external_facets) {
                    external_facets=0;
                    return;
                }
                internal_facets=0;
                ++external_facets;
                return;
            }
            ++internal_facets;
        }
        bool isDefault() {
            return (0==internal_facets) && (0==external_facets);
        }
        const unsigned int& external() const {
            return external_facets;
        }
        const unsigned int& internal() const {
            return internal_facets;
        }
        unsigned int toUint() const {
            
        }
        friend ostream& operator<<(ostream& o, const OCubeIterator& cit);
          bool operator<(const OCubeIterator& other) const {
              if (this->external_facets<other.external_facets) {
                  return true;
              } else if (this->external_facets>other.external_facets) {
                  return false;
              } else if (this->internal_facets<other.internal_facets) {
                  return true;
              } else if (this->internal_facets>other.internal_facets) {
                  return false;
              }
              return false;
          }
    private:
        const static unsigned int EFACETS_NUM=24;
        const static unsigned int IFACETS_NUM=12;
        const static unsigned int EFACETS_MAX=InPower<2, EFACETS_NUM>::result;
        const static unsigned int IFACETS_MAX=InPower<2, IFACETS_NUM>::result;
        /// 24 bit for external facets
        unsigned int external_facets;
        /// 12 bits for internal factes
        unsigned int internal_facets;
};

ostream& operator<<(ostream& o, const OCubeIterator& cit) {
    return o
    << '[' << cit.external_facets << ']'
    << '/' << OCubeIterator::EFACETS_NUM
    << " + "
    << '[' << cit.internal_facets << ']'
    << '/' << OCubeIterator::IFACETS_NUM
    ;
}


unsigned int bitn2num(unsigned int num) {
    if (0==num) {
        return 0;
    }
    unsigned int result=1;
    result<<=(num-1);
    return result;
}

void printSet(const std::set<OCubeIterator>& s) {
    std::cout << "set\n";
    for (std::set<OCubeIterator>::const_iterator it=s.begin();it!=s.end();++it) {
        std::cout << *it << " ; ";
    }
    std::cout << std::endl << s.size();
    std::cout << std::endl << std::endl;
}

bool haveBit(unsigned int number, unsigned int pos) {
    unsigned int tmp=1;
    tmp<<=pos;
    return pos&number;
}

int main() {
    //cerr << OCubeIterator() << endl;
    OCubeIterator ocit;
    using namespace std;
    vector<vector<int> > data;
    for (unsigned int i=0;i<48;++i) {
        vector<int> v;
        for (unsigned int j=0;j<=36;++j) {
            v.push_back(0);
        }
        data.push_back(v);
    }
    #include "data.h"
    std::set<OCubeIterator> result;
    do {
        const unsigned int efaces=ocit.external();
        const unsigned int ifaces=ocit.internal();
        for (unsigned int rotationNum=0;rotationNum<48;++rotationNum) {
            unsigned int efacesR=0;
            unsigned int ifacesR=0;
            unsigned int i=1;
            for (unsigned int in=0;in<12;++in,++i) {
                if (!haveBit(ifaces, i)) continue;
                int result=data[rotationNum][i];
                ifacesR|=bitn2num(result);
            }
            for (unsigned int ex=0;ex<24;++ex,++i) {
                if (!haveBit(efaces, i)) continue;
                int result=data[rotationNum][i];
                efacesR|=bitn2num(result);
            }
            result.insert(OCubeIterator(ifacesR, efacesR));
        }
        //cout << ocit << endl;
        if (0==ifaces) printSet(result);
        ++ocit;
    } while (!ocit.isDefault());
    printSet(result);
}

