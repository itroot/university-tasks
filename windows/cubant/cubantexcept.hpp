#ifndef CUBANT_EXCEPT_CXX_H_
#define CUBANT_EXCEPT_CXX_H_ 1

#include <stdexcept>
#include <string>

namespace CubantCore {
    class cubant_exception : public std::runtime_error {
        public:
            cubant_exception(const std::string& _what)
            : std::runtime_error(_what)
            {}
    };

    class cubant_parse_exception : public cubant_exception {
        public:
            cubant_parse_exception(const std::string& _what)
            : cubant_exception(_what)
            {}
    };
}
#endif
