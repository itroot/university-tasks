#ifndef CUBANT_API_CXX_H_
#define CUBANT_API_CXX_H_

#include <assert.h>
#include <cubant/cubantexcept.hpp>

namespace CubantCore {

    /**
     * Type of cubant.
     *
     */
    class CubantType {
        public:
            enum Type {
                Nothing =  0,
                NoShift =  1,
                Shift =    2,
                Spread =   3
            };
            CubantType(Type _type=Nothing)
            : type(_type)
            {}
            void setType(Type _type) {
                type=_type;
            }
            void setType(unsigned int _type) {
                if (_type>3) {
                    throw cubant_exception("Invalid type conversion from uint");
                }
                type=static_cast<Type>(_type);
            }
            Type getType() const {
                return type;
            }
            static CubantType char2type(char c);
            static char type2char(CubantType t);
        private:
            Type type;
    };
}

#endif
