#include <iostream>

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

    private:
        const static unsigned int EFACETS_NUM=24;
        const static unsigned int IFACETS_NUM=12;
        const static unsigned int EFACET_MAX=InPower<2, EFACETS_NUM>::result;
        const static unsigned int IFACET_MAX=InPower<2, IFACETS_NUM>::result;
        /// 24 bit for external facets
        unsigned int external_facets;
        /// 12 bits for internal factes
        unsigned int internal_facets;
};

int main() {

}
