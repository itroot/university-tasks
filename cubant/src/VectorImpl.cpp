#include <cubant/VectorImpl.hpp>
#include <cubant/cubantexcept.hpp>

#include <iostream>

CubantCore::VectorImpl::
VectorImpl(unsigned int _dimension)
    : dimension(_dimension)
    , values(dimension)
{}

CubantCore::CubantType&
CubantCore::VectorImpl::
operator[](unsigned int index) {
    #ifndef NDEBUG
    if (index>=dimension) {
        throw cubant_parse_exception("index >= dimension");
    }
    #endif
    return values[index];
}


const CubantCore::CubantType&
CubantCore::VectorImpl::
operator[](unsigned int index) const {
    #ifndef NDEBUG
    if (index>=dimension) {
        throw cubant_parse_exception("index >= dimension");
    }
    #endif
    return values[index];
}

unsigned int
CubantCore::VectorImpl::
size() const {
    #ifndef NDEBUG
    assert(dimension==values.size());
    #endif
    return dimension;
}

std::string
CubantCore::VectorImpl::
toString() const {
    string result;
    #ifndef NDEBUG
    assert(dimension==values.size());
    assert(dimension>0);
    #endif
    result+='/';
    for (size_t i=0;i<dimension-1;++i) {
        result+=CubantType::type2char(values[i]);
        result+=",";
    }
    result+=CubantType::type2char(values.back());
    result+='/';
    return result;
}

// FIXME must be template
CubantCore::VectorImpl
CubantCore::VectorImpl::
intersect(const VectorImpl& lhs, const VectorImpl& rhs) {
    if (lhs.size()!=rhs.size()) {
        throw cubant_exception("Can't intersect different-sized cubants");
    }
    unsigned int size=lhs.size();
    VectorImpl result(size);
    for (unsigned int i=0;i<size;++i) {
        // we use binary
        result[i].setType(lhs[i].getType()&rhs[i].getType());
    }
    return result;
}

CubantCore::VectorImpl
CubantCore::VectorImpl::
farEdge(const VectorImpl& lhs, const VectorImpl& rhs) {
        if (lhs.size()!=rhs.size()) {
        throw cubant_exception("Can't far-egde different-sized cubants");
    }
    unsigned int size=lhs.size();
    VectorImpl result(size);
    for (unsigned int i=0;i<size;++i) {
        if (CubantType::Nothing==lhs[i].getType() ||
            CubantType::Nothing==rhs[i].getType()) {
            throw cubant_exception("Can't far-egde pseudo cubants");
        }
        if (CubantType::NoShift==lhs[i].getType()) {
            result[i].setType(CubantType::NoShift);
        } else if (CubantType::Shift==lhs[i].getType()) {
            result[i].setType(CubantType::Shift);
        } else if (CubantType::Spread==lhs[i].getType()) {
            if (CubantType::NoShift==rhs[i].getType()) {
                result[i].setType(CubantType::Shift);
            } else if (CubantType::Shift==rhs[i].getType()) {
                result[i].setType(CubantType::NoShift);
            } else {
                result[i].setType(CubantType::Spread);
            }
        }
        //result[i].setType(lhs[i].getType()&rhs[i].getType());
    }
    return result;
}

CubantCore::VectorImpl
CubantCore::VectorImpl::
convexHull(const VectorImpl& lhs,
           const VectorImpl& rhs) {
    if (lhs.size()!=rhs.size()) {
        throw cubant_exception("Can't find convex hull with different-sized cubants");
    }
    unsigned int size=lhs.size();
    VectorImpl result(size);
    for (unsigned int i=0;i<size;++i) {
        // we use binary
        result[i].setType(lhs[i].getType()|rhs[i].getType());
    }
    return result;
}



