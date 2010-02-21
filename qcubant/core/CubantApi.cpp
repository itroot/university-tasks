#include <core/CubantApi.hpp>
#include <core/cubantexcept.hpp>

#include <stdexcept>
#include <vector>


CubantCore::CubantType
CubantCore::CubantType::
char2type(char c) {
    CubantType cubantType;
    switch(c) {
        case 'Z' : {
            cubantType.setType(CubantType::Nothing);
        } break;
        case '0' : {
            cubantType.setType(CubantType::NoShift);
        } break;
        case '1' : {
            cubantType.setType(CubantType::Shift);
        } break;
        case '2' : {
            cubantType.setType(CubantType::Spread);
        } break;
        default : {
            throw std::range_error("No such char");
        }
    }
    return cubantType;
}

char
CubantCore::CubantType::
type2char(CubantCore::CubantType t) {
    char c;
    switch(t.getType()) {
        case CubantType::Nothing : {
            c='Z';
        } break;
        case CubantType::NoShift : {
            c='0';
        } break;
        case CubantType::Shift : {
            c='1';
        } break;
        case CubantType::Spread : {
            c='2';
        } break;
        default : {
            throw std::range_error("No such type");
        }
    }
    return c;
}