#include <cubant/Cubant.hpp>

#include <iostream>

using namespace std;
using namespace CubantCore;

int main() {
    std::string cubant_str="/1,1,1,1,2,0,Z/";
    cubant_t c(cubant_str);
    cout << "Was: " << cubant_str << " now: " << c.toString() << endl;
    cout << "hausdorf: " << cubant_t::hausdorf(cubant_t("/0,2,2,0/"), cubant_t("/1,2,1,1/")) << endl;
    return cubant_str!=c.toString();
}
