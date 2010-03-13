#include <iostream>
#include <string>

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
        friend ostream& operator<<(ostream& o, const OCubeIterator& cit);
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

int main() {
    //cerr << OCubeIterator() << endl;
    OCubeIterator ocit;
    do {
        //cout << ocit << endl;
        ++ocit;
    } while (!ocit.isDefault());
}
