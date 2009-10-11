#ifndef ETALON_DIAGS_H_
#define ETALON_DIAGS_H_

using namespace std;

#include <vector>
#include "Line3D.h"
#include "SimplexModel.h"

class EtalonDiags {
  public:
    enum Type {
      T_0602,
      T_1331,
      T_2060,
      T_2222,
      T_4004,
      T_UNKNOWN
    };
    // not thread-safe =)))
    static void init();
    static const vector<Diagonal>& getDiagsByType(Type type);
    static const vector<SimplexModel>& getSimplexByType(Type type);
  private:
    static vector<Diagonal> v_0602;
    static vector<Diagonal> v_1331;
    static vector<Diagonal> v_2060;
    static vector<Diagonal> v_2222;
    static vector<Diagonal> v_4004;

    static vector<SimplexModel> m_0602;
    static vector<SimplexModel> m_1331;
    static vector<SimplexModel> m_2060;
    static vector<SimplexModel> m_2222;
    static vector<SimplexModel> m_4004;

    static bool is_initialized;
};

#endif
