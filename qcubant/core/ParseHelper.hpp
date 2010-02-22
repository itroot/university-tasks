#ifndef PARSE_HELPER_CXX_H_
#define PARSE_HELPER_CXX_H_

#include <string>
#include <ctype.h>

#include <assert.h>



namespace ParseHelper {
    using std::string;

    class ParserString {
        public:
            ParserString(const string& _str)
             : str(_str)
             , start(0)
             , end(str.size())
             , pos(0)
            {
                #ifndef NDEBUG
                assert(end>start);
                #endif
            }
            ParserString(const string& _str,
                         const size_t _start,
                         const size_t _end)
             : str(_str)
             , start(_start)
             , end(_end)
             , pos(start) {
                 #ifndef NDEBUG
                 assert(end>start);
                 assert(end<=str.size());
                 assert(start<=str.size());
                 #endif
             }
             void operator++() const {
                 ++pos;
             }
             unsigned int skipSpaces() const {
                 unsigned int old_pos=pos;
                 while(pos<end) {
                     if (isspace(str[pos])) {
                         ++pos;
                     } else {
                         break;
                     }
                 }
                return pos-old_pos;
             }
             bool advanceOnChar(char c) const {
                 if (c==str[pos]) {
                     ++pos;
                     return true;
                 }
                 return false;
             }
             char readChar() const {
                 return str[pos];
             }
             char readCharSkipSpaces() const {
                 skipSpaces();
                 if (end==pos) {
                     return ' ';
                 } else {
                     return str[pos++];
                 }
             }
             size_t getPosition() const {
                 #ifndef NDEBUG
                 assert(pos>=start);
                 assert(pos<=end);
                 #endif
                 return pos;
             }
        private:
            const string& str;
            const size_t start;
            const size_t end;
            mutable size_t pos;
    };
}
#endif
