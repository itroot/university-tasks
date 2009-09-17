#include <cubant/Cubant.hpp>

#include <iostream>

using namespace std;
using namespace CubantCore;

int main() {
    std::string cubant1_str="/Z,Z,Z,Z,0,0,0,0,1,1,1,1,2,2,2,2/";
    std::string cubant2_str="/Z,0,1,2,Z,0,1,2,Z,0,1,2,Z,0,1,2/";
    cubant_t c1(cubant1_str);
    cubant_t c2(cubant2_str);
    cout << c1.toString() << endl
         << c2.toString() << endl
         << cubant_t::intersect(c1,c2).toString()
         << endl;
    return "/Z,Z,Z,Z,Z,0,Z,0,Z,Z,1,1,Z,0,1,2/"
    !=cubant_t::intersect(c2,c1).toString();
}
