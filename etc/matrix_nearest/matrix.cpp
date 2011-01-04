#include <iostream>
#include <vector>
#include <map>
#include <string>

// 1 - +
// 0 - 0
// -1 - -


typedef std::vector<std::string> PointsList;


unsigned int numOfDiffs(const std::string& lhs, const std::string& rhs) {
    if (rhs.size()!=lhs.size()) {
        throw 1;
    }
    unsigned int result=0;
    for (unsigned int i=0; i<rhs.size(); ++i) {
        if (rhs[i]!=lhs[i]) {
            ++result;
        }
    }
    return result;
}

bool isBadPoint(const std::string& str) {
    if ("0000"==str)
    /*
    for (unsigned int i=0;i<str.length();++i) {
        if ('0'!=str[i]) {
            return false;
        }
    }
    */
    return true;
    return false;
}

PointsList generateFacets(unsigned int dimension) {
    PointsList result;
    if (1==dimension) {
        result.push_back("+");
        result.push_back("0");
        result.push_back("-");
    } else {
        PointsList tmp;
        tmp=generateFacets(dimension-1);
        for (unsigned int i=0;i<tmp.size();++i) {
            result.push_back(tmp[i]+"+");
            result.push_back(tmp[i]+"0");
            result.push_back(tmp[i]+"-");
        }
    }
    PointsList rresult;
    for (unsigned int i=0;i<result.size();++i) {
        if (!isBadPoint(result[i])) {
            rresult.push_back(result[i]);
        }
    }
    return rresult;
}


int print_matrix(unsigned int dimension) {
    PointsList points;
    points=generateFacets(dimension);
    for (unsigned int i=0;i<dimension;++i) {
        for (unsigned int j=0;j<dimension;++j) {
            std::cout << " " ;
        }
        std::cout << " " ;
        for (unsigned int j=0;j<points.size();++j) {
            std::cout << points[j][i];
        }
        std::cout << std::endl ;
    }
    std::cout << std::endl ;
    for (unsigned int i=0;i<points.size();++i) {
        std::cout << points[i] << " ";
        for (unsigned int j=0;j<points.size();++j) {
            unsigned int diffs=numOfDiffs(points[i], points[j]);
            if (1==diffs) {
                std::cout << "X";
            } else {
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    print_matrix(4);
}

