#include <cubant/Cubant.hpp>

#include <iostream>

using namespace std;
using namespace CubantCore;

int main() {
    GreedyCubant c("/1,1,1,1,2,0,Z/");
    cout << c.toString() << endl;
}
