#include <cubant/CubantApi.hpp>

#include <stdexcept>

CubantCore::CubantType
CubantCore::
char2type(char c) {
    CubantType cubantType;
    switch(c) {
        case 'Z' : {
            cubantType.type=CubantType::Nothing;
        } break;
        case '0' : {
            cubantType.type=CubantType::NoShift;
        } break;
        case '1' : {
            cubantType.type=CubantType::Shift;
        } break;
        case '2' : {
            cubantType.type=CubantType::Spread;
        } break;
        default : {
            throw std::range_error("No such char");
        }
    }
    return cubantType;
}

char
CubantCore::
type2char(CubantCore::CubantType t) {
    char c;
    switch(t.type) {
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