#ifndef VECTOR_IMPL_CXX_H_
#define VECTOR_IMPL_CXX_H_

#include <core/CubantApi.hpp>

#include <vector>
#include <string>

namespace CubantCore {
    using std::vector;
    using std::string;

    class VectorImpl {
        public:
            explicit VectorImpl(unsigned int _dimension);
            CubantType& operator[](unsigned int index);
            const CubantType& operator[](unsigned int index) const;
            unsigned int size() const;
            string toString() const;  // FIXME stringable
            static VectorImpl intersect(const VectorImpl& lhs,
                                        const VectorImpl& rhs);
            static VectorImpl farEdge(const VectorImpl& lhs,
                                      const VectorImpl& rhs);
            static VectorImpl convexHull(const VectorImpl& lhs,
                                         const VectorImpl& rhs);
        private:
            unsigned int dimension;
            vector<CubantType> values;
    };
}

#endif
