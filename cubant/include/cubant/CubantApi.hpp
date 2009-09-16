#ifndef CUBANT_API_CXX_H_
#define CUBANT_API_CXX_H_ 1

#include <assert.h>

namespace CubantCore {
    struct CubantType {
        CubantType(): type(Nothing) {}
        enum Type {
            Nothing =  0,
            NoShift =  1,
            Shift =    2,
            Spread =   3
        };
        Type type;
    };

    CubantType char2type(char c);
    char type2char(CubantType t);
}

#endif
