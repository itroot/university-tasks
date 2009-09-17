#ifndef CUBANT_CXX_H_
#define CUBANT_CXX_H_

#include <cubant/CubantApi.hpp>
#include <cubant/ParseHelper.hpp>
#include <cubant/VectorImpl.hpp>


#include <stdexcept>
#include <utility>
#include <iostream>

namespace CubantCore {

    using std::range_error;
    using std::runtime_error;

    // parser helper FIXME
    // /Z,0,1,2/
    template<class Impl>
    Impl getImplFromString(const ParseHelper::ParserString& pstr);

    template<class Impl>
    class Cubant {
        public:
            Cubant(){}
            explicit Cubant(const Impl& _impl)
            : impl(_impl)
            {}
            explicit Cubant(const string& _str)
            : impl(getImplFromString<Impl>(_str))
            {
            }
            string toString() {
                return impl.toString();
            }
            bool isPseudo() {
                for(unsigned int i=0; i<impl.size(); ++i) {
                    if (CubantType::Nothing==impl[i].getType()) {
                        return true;
                    }
                }
                return false;
            }
            unsigned int numOfTypes(CubantType::Type type) {
                unsigned int result;
                for(unsigned int i=0; i<impl.size(); ++i) {
                    if (impl[i].getType()==type) {
                        ++ result;
                    }
                }
                return result;
            }
            // make friend
            static Cubant intersect(const Cubant& lhs, const Cubant& rhs) {
                return Cubant(Impl::intersect(lhs.impl, rhs.impl));
            }
            // make friend
            static bool isIntersecting(const Cubant& lhs, const Cubant& rhs) {
                return !Cubant(Impl::intersect(lhs.impl, rhs.impl)).isPseudo();
            }
            static unsigned int distance(const Cubant& lhs, const Cubant& rhs) {
                Cubant tmp=intersect(lhs, rhs);
                return tmp.numOfTypes(CubantType::Nothing);
            }
            // make friend
            static unsigned int hausdorf(const Cubant& lhs, const Cubant& rhs) {
                return std::max(
                    distance(lhs, farEdge(rhs, lhs)),
                    distance(rhs, farEdge(lhs, rhs))
                );
            }
        private:
            static Cubant farEdge(const Cubant& lhs, const Cubant& rhs) {
                return Cubant(Impl::farEdge(lhs.impl, rhs.impl));
            }
            Impl impl;
    };

    typedef Cubant<VectorImpl> cubant_t;
}

// implementation pf templates
template<class Impl>
Impl
CubantCore::
getImplFromString(const ParseHelper::ParserString& pstr) {
    vector<char> keys;
    if ('/'!=pstr.readCharSkipSpaces()) {
        throw runtime_error("Don't have /");
    }
    bool now_comma=false;
    char c;
    while('/'!=(c=pstr.readCharSkipSpaces())) {
        if (','==c) {
            if (now_comma) {
                now_comma=false;
                continue;
            } else {
                throw runtime_error("Double comma");
            }
        } else {
           if (now_comma) {
               throw runtime_error("Expected comma");
           } else {
               now_comma=true;
           }
        }
        switch (c) {
            case 'Z':
            case '0':
            case '1':
            case '2': {
                keys.push_back(c);
            } break;
            default: {
                throw runtime_error(string("Parse error: unexpected ")+c);
            } break;
        }
    }
    if (0==keys.size()) {
        throw("Find no cubant letters");
    }
    Impl impl(static_cast<unsigned int>(keys.size()));
    for (size_t i=0;i<keys.size();++i) {
        impl[i]=CubantType::char2type(keys[i]);
    }
    return impl;
}



#endif
