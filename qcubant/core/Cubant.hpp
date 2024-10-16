#ifndef CUBANT_CXX_H_
#define CUBANT_CXX_H_

#include <core/CubantApi.hpp>
#include <core/ParseHelper.hpp>
#include <core/VectorImpl.hpp>


#include <stdexcept>
#include <utility>
#include <iostream>
#include <set>


namespace CubantCore {

    using std::range_error;
    using std::runtime_error;
    using std::cerr;
    using std::cout;
    using std::endl;

    // parser helper FIXME
    // /Z,0,1,2/
    template<class Impl>
    Impl getImplFromString(const ParseHelper::ParserString& pstr);

    template<class Impl>
    class Cubant {
        public:
            typedef std::vector<int> point_t; // -1 -- means 2
            typedef std::set<point_t> points_t;
            typedef std::vector<int> vector_diff_t; // -1 -- means 2
            explicit Cubant(const Impl& _impl)
            : impl(_impl)
            {
                for (unsigned int i=0;i<impl.size();++i) {
                    m_diff_vector.push_back(0);
                }
            }
            explicit Cubant(const string& _str="/0,0,0/") // FIXME default
            : impl(getImplFromString<Impl>(_str))
            {
            }
            string toString() {
                return impl.toString();
            }
            const CubantType& operator[](unsigned int i) const {
              return impl[i];
            }
            CubantType& operator[](unsigned int i) {
              return impl[i];
            }
            size_t size() const {
              return impl.size();
            }
            bool isPseudo() {
                for(unsigned int i=0; i<impl.size(); ++i) {
                    if (CubantType::Nothing==impl[i].getType()) {
                        return true;
                    }
                }
                return false;
            }
            unsigned int numOfTypes(CubantType::Type type) {
                unsigned int result;
                for(unsigned int i=0; i<impl.size(); ++i) {
                    if (impl[i].getType()==type) {
                        ++ result;
                    }
                }
                return result;
            }
            // make friend
            static Cubant intersect(const Cubant& lhs, const Cubant& rhs) {
                return Cubant(Impl::intersect(lhs.impl, rhs.impl));
            }
            // make friend
            static Cubant convexHull(const Cubant& lhs, const Cubant& rhs) {
                return Cubant(Impl::convexHull(lhs.impl, rhs.impl));
            }
            // make friend
            static bool isIntersecting(const Cubant& lhs, const Cubant& rhs) {
                return !Cubant(Impl::intersect(lhs.impl, rhs.impl)).isPseudo();
            }
            static unsigned int distance(const Cubant& lhs, const Cubant& rhs) {
                Cubant tmp=intersect(lhs, rhs);
                return tmp.numOfTypes(CubantType::Nothing);
            }
            // make friend
            static unsigned int hausdorf(const Cubant& lhs, const Cubant& rhs) {
                return std::max(
                    distance(lhs, farEdge(rhs, lhs)),
                    distance(rhs, farEdge(lhs, rhs))
                );
            }
            points_t getPoints() {
              points_t result;
              // creating pseudo point from cubant
              point_t pseudoPoint;
              for (unsigned int i=0;i<size();++i) {
                switch (this->operator[](i).getType()) {
                  case CubantType::NoShift :{pseudoPoint.push_back(0);} break;
                  case CubantType::Shift :{pseudoPoint.push_back(2);} break;
                  case CubantType::Spread :{pseudoPoint.push_back(-1);} break; // means spread
                  default: {throw cubant_exception("Can't create point from this cubant");} break;
                }
              }
              toPoints(pseudoPoint, 0, result);
              return result;
            }
        private:
          // kind of bad code =)
            static void toPoints(const point_t& pseudoPoint, unsigned int pos, points_t& result) {
              while(pos<pseudoPoint.size() && -1!=pseudoPoint[pos]) {
                ++pos;
              }
              if (pseudoPoint.size()==pos) {
                //cerr << "INSERT" << endl;
                result.insert(pseudoPoint);
                //cerr << "SIZE: " << result.size() << endl;
                return;
              }
              //cerr << "GO" << endl;
              if (-1==pseudoPoint[pos]) { //pseudo
                point_t p1=pseudoPoint;
                point_t p2=pseudoPoint;
                point_t p3=pseudoPoint;

                p1[pos]=0;
                p2[pos]=1; // we can speedup using int
                p3[pos]=2;

                toPoints(p1, pos+1, result);
                toPoints(p2, pos+1, result);
                toPoints(p3, pos+1, result);
                return;
              }
              throw cubant_exception("Can't be there");
            }
      public:
          // FIXME diff vector;
          vector_diff_t m_diff_vector;
        /*
            static double hausdorff_distance(const points_t& p1, const points_t& p2) {
              // distances between points
              double result=0;
              double* table=new double[p1.size()*p2.size()];
              size_t s=p2.size();
              int i=0;
              for (points_t::iterator it=p1.begin();it!=p1.end();++it,++i) {
                int j=0;
                for (points_t::iterator jt=p2.begin();jt!=p2.end();++jt,++j) {
                  double dist=0;
                  for (size_t k=0;k<it->size();++k) {
                    dist+=(*it)[k]*(*it)[k]+(*jt)[k]*(*jt)[k];
                  }
                  table[s*i+j]=dist;
                  //cout << dist << " " ;
                }
                //cout << endl;
              }
              delete[] table;
              return result;
            }
            */
      private:
            static Cubant farEdge(const Cubant& lhs, const Cubant& rhs) {
                return Cubant(Impl::farEdge(lhs.impl, rhs.impl));
            }
            Impl impl;
    };
    typedef Cubant<VectorImpl> cubant_t;
}

// implementation pf templates
template<class Impl>
Impl
CubantCore::
getImplFromString(const ParseHelper::ParserString& pstr) {
    vector<char> keys;
    if ('/'!=pstr.readCharSkipSpaces()) {
        throw runtime_error("Don't have /");
    }
    bool now_comma=false;
    char c;
    while('/'!=(c=pstr.readCharSkipSpaces())) {
        if (','==c) {
            if (now_comma) {
                now_comma=false;
                continue;
            } else {
                throw runtime_error("Double comma");
            }
        } else {
           if (now_comma) {
               throw runtime_error("Expected comma");
           } else {
               now_comma=true;
           }
        }
        switch (c) {
            case 'Z':
            case '0':
            case '1':
            case '2': {
                keys.push_back(c);
            } break;
            default: {
                throw runtime_error(string("Parse error: unexpected ")+c);
            } break;
        }
    }
    if (0==keys.size()) {
        throw("Find no cubant letters");
    }
    Impl impl(static_cast<unsigned int>(keys.size()));
    for (size_t i=0;i<keys.size();++i) {
        impl[i]=CubantType::char2type(keys[i]);
    }
    return impl;
}



#endif
