#ifndef CUBANT_CXX_H_
#define CUBANT_CXX_H_ 1

#include <cubant/CubantApi.hpp>
#include <cubant/ParseHelper.hpp>

#include <vector>
#include <string>
#include <stdexcept>

#include <iostream>

namespace CubantCore {
    using std::vector;
    using std::string;

    using std::range_error;
    using std::runtime_error;

    class VectorImpl {
        public:
            explicit VectorImpl(unsigned int _dimension)
            : dimension(_dimension)
            , values(dimension)
            {}
            CubantType& operator[](unsigned int index) {
                #ifndef NDEBUG
                if (index>=dimension) {
                    throw range_error("index >= dimension");
                }
                #endif
                return values[index];
            }
            unsigned int size() const {
                #ifndef NDEBUG
                assert(dimension==values.size());
                #endif
                return dimension;
            }
            // FIXME stringable
            string toString() const {
                string result;
                #ifndef NDEBUG
                assert(dimension==values.size());
                assert(dimension>0);
                #endif
                result+='/';
                for (size_t i=0;i<dimension-1;++i) {
                    result+=type2char(values[i]);
                    result+=",";
                }
                result+=type2char(values.back());
                result+='/';
                return result;
            }
        private:
            unsigned int dimension;
            vector<CubantType> values;
    };

    // parser helper FIXME
    // /Z,0,1,2/
    template<class Impl>
    Impl getImplFromString(const ParseHelper::ParserString& pstr) {
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
            impl[i]=char2type(keys[i]);
        }
        return impl;
    }

    template<class Impl>
    class Cubant {
        public:
            Cubant(){}
            Cubant(const Impl& _impl)
            : impl(_impl)
            {}
            Cubant(const string& _str)
            : impl(getImplFromString<Impl>(_str))
            {
            }
            string toString() {
                return impl.toString();
            }
        private:
            Impl impl;
    };

    typedef Cubant<VectorImpl> GreedyCubant;
}

#endif
