#include <ui/reper.h>

#include <stdexcept>
#include <iostream>
#include <cmath>

Reper::
Reper(unsigned int _num, unsigned int _height, unsigned int _width)
    : num(_num)
    , height(_height)
    , width(_width)
{
    if (0==num) {
        throw std::runtime_error("Reper with 0 dimension");
    }
    for (size_t i=0; i<num; ++i) {
        vectors.push_back(std::make_pair(width*(i-num/2)+((num%2)?0:width/2), -height));
        double angle=2*M_PI*((i-num/2.0)/num);
        vectors3d.push_back(Coords3D(width*sin(angle)*COEFF_3D,-height, width*cos(angle)*COEFF_3D));
    }
    // std::cerr << "!!!!!!!!!!!!\n";
}

void
Reper::
set2DVector(unsigned int vectorNum, int x, int y) {
    if (vectorNum>num) {
        throw std::runtime_error("Reper size out of dimension.");
    }
    vectors[vectorNum].first=x;
    vectors[vectorNum].second=y;
    // std::cerr << "SET\n";
    // 3D
    double angle=2*M_PI*((vectorNum-num/2.0)/num);
    vectors3d[vectorNum].x=x*sin(angle)*COEFF_3D;
    vectors3d[vectorNum].y=y;
    vectors3d[vectorNum].z=x*cos(angle)*COEFF_3D;
}

unsigned int
Reper::
getNum() {
    return num;
}
unsigned int
Reper::
getHeight() {
    return height;
}

unsigned int
Reper::
getWidth() {
    return width;
}

int
Reper::
getVectorProjection(unsigned int vectorNum, unsigned int coord) {
    //std::cout << "gvp " << vectorNum << " " << coord << std::endl;
    if (0==coord) {
        return vectors[vectorNum].first;
    } else if (1==coord) {
        return vectors[vectorNum].second;
    };
    throw std::out_of_range("No such vector dimension");
}

int
Reper::
getVectorProjection3D(unsigned int vectorNum, unsigned int coord) {
    //std::cout << "gvp3d " << vectorNum << " " << coord << std::endl;
    if (0==coord) {
        return vectors3d[vectorNum].x;
    } else if (1==coord) {
        return vectors3d[vectorNum].y;
    } else if (2==coord) {
        return vectors3d[vectorNum].z;
    } 
    throw std::out_of_range("No such vector3d dimension");
}

