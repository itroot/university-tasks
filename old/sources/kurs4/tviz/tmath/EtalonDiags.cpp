#include "EtalonDiags.h"
bool EtalonDiags::is_initialized=false;

vector<Diagonal> EtalonDiags::v_0602;
vector<Diagonal> EtalonDiags::v_1331;
vector<Diagonal> EtalonDiags::v_2060;
vector<Diagonal> EtalonDiags::v_2222;
vector<Diagonal> EtalonDiags::v_4004;

vector<SimplexModel> EtalonDiags::m_0602;
vector<SimplexModel> EtalonDiags::m_1331;
vector<SimplexModel> EtalonDiags::m_2060;
vector<SimplexModel> EtalonDiags::m_2222;
vector<SimplexModel> EtalonDiags::m_4004;

void EtalonDiags::init() {
  if (is_initialized) return;
  is_initialized=true;

  v_0602.clear();
  v_1331.clear();
  v_2060.clear();
  v_2222.clear();
  v_4004.clear();


  m_0602.clear();
  m_1331.clear();
  m_2060.clear();
  m_2222.clear();
  m_4004.clear();

  // Gena start

  // itroot start
  m_0602.push_back(SimplexModel(Point3D(-1,-1,-1), Point3D(1,1,1), Point3D(-1,1,1), Point3D(-1,1,-1)));
  m_0602.push_back(SimplexModel(Point3D(-1,-1,-1), Point3D(1,1,1), Point3D(1,-1,1), Point3D(-1,-1,1)));
  m_0602.push_back(SimplexModel(Point3D(-1,-1,-1), Point3D(1,1,1), Point3D(-1,-1,1), Point3D(-1,1,1)));
  m_0602.push_back(SimplexModel(Point3D(-1,-1,-1), Point3D(1,1,1), Point3D(1,-1,1), Point3D(1,-1,-1)));
  m_0602.push_back(SimplexModel(Point3D(-1,-1,-1), Point3D(1,1,1), Point3D(1,-1,-1), Point3D(1,1,-1)));
  m_0602.push_back(SimplexModel(Point3D(-1,-1,-1), Point3D(1,1,1), Point3D(1,1,-1), Point3D(-1,1,-1)));
  
  m_1331.push_back(SimplexModel(Point3D(1,1,1), Point3D(1,1,-1), Point3D(1,-1,-1), Point3D(-1,1,-1)));
  m_1331.push_back(SimplexModel(Point3D(1,1,1), Point3D(-1,-1,-1), Point3D(-1,1,-1),Point3D(1,-1,-1)));
  m_1331.push_back(SimplexModel(Point3D(1,1,1), Point3D(-1,-1,-1), Point3D(1,-1,1), Point3D(1,-1,-1)));
  m_1331.push_back(SimplexModel(Point3D(1,1,1), Point3D(-1,-1,-1), Point3D(-1,1,1), Point3D(-1,1,-1)));
  m_1331.push_back(SimplexModel(Point3D(1,1,1), Point3D(-1,-1,-1), Point3D(-1,1,1), Point3D(-1,-1,1)));
  m_1331.push_back(SimplexModel(Point3D(1,1,1), Point3D(-1,-1,-1), Point3D(-1,-1,1), Point3D(1,-1,1)));
  
  m_2060.push_back(SimplexModel(Point3D(-1,-1,-1), Point3D(-1,1,1), Point3D(-1,-1,1), Point3D(1,-1,1)));
  m_2060.push_back(SimplexModel(Point3D(1,1,1), Point3D(1,1,-1), Point3D(1,-1,-1), Point3D(-1,1,-1)));
  m_2060.push_back(SimplexModel(Point3D(-1,-1,-1), Point3D(1,1,1), Point3D(-1,1,1), Point3D(1,-1,1)));
  m_2060.push_back(SimplexModel(Point3D(-1,-1,-1), Point3D(1,1,1), Point3D(-1,1,1), Point3D(-1,1,-1)));
  m_2060.push_back(SimplexModel(Point3D(-1,-1,-1), Point3D(1,1,1), Point3D(-1,1,-1), Point3D(1,-1,-1)));
  m_2060.push_back(SimplexModel(Point3D(-1,-1,-1), Point3D(1,1,1), Point3D(1,-1,1), Point3D(1,-1,-1)));
  
  m_2222.push_back(SimplexModel(Point3D(-1,-1,1), Point3D(1,1,1), Point3D(-1,1,1), Point3D(-1,1,-1)));
  m_2222.push_back(SimplexModel(Point3D(-1,-1,1), Point3D(1,1,1), Point3D(1,-1,1), Point3D(1,-1,-1)));
  m_2222.push_back(SimplexModel(Point3D(-1,-1,-1), Point3D(1,1,1), Point3D(-1,1,-1), Point3D(1,1,-1)));
  m_2222.push_back(SimplexModel(Point3D(-1,-1,-1), Point3D(1,1,1), Point3D(1,1,-1), Point3D(1,-1,-1)));
  m_2222.push_back(SimplexModel(Point3D(-1,-1,-1), Point3D(1,1,1), Point3D(-1,-1,1), Point3D(-1,1,-1)));
  m_2222.push_back(SimplexModel(Point3D(-1,-1,-1), Point3D(1,1,1), Point3D(-1,-1,1), Point3D(1,-1,-1)));
  
  m_4004.push_back(SimplexModel(Point3D(1,1,1), Point3D(-1,-1,1), Point3D(1,-1,-1), Point3D(-1,1,-1)));
  m_4004.push_back(SimplexModel(Point3D(1,1,1), Point3D(-1,1,-1), Point3D(1,-1,-1), Point3D(1,1,-1)));
  m_4004.push_back(SimplexModel(Point3D(1,1,1), Point3D(-1,-1,1), Point3D(1,-1,-1), Point3D(1,-1,1)));
  m_4004.push_back(SimplexModel(Point3D(1,1,1), Point3D(-1,-1,1), Point3D(-1,1,-1), Point3D(-1,1,1)));
  m_4004.push_back(SimplexModel(Point3D(-1,-1,-1), Point3D(-1,-1,1), Point3D(-1,1,-1), Point3D(1,-1,-1)));
  // itroot end

  v_0602.push_back(Diagonal(Point3D(-1,-1,-1),Point3D(-1,1,1)));
  v_0602.push_back(Diagonal(Point3D(-1,-1,-1),Point3D(1,-1,1)));
  v_0602.push_back(Diagonal(Point3D(-1,-1,-1),Point3D(1,1,-1)));
  v_0602.push_back(Diagonal(Point3D(1,1,1),Point3D(-1,1,-1)));
  v_0602.push_back(Diagonal(Point3D(1,1,1),Point3D(-1,-1,1)));
  v_0602.push_back(Diagonal(Point3D(1,1,1),Point3D(1,-1,-1)));

  v_1331.push_back(Diagonal(Point3D(-1,-1,-1),Point3D(-1,1,1)));
  v_1331.push_back(Diagonal(Point3D(-1,-1,-1),Point3D(1,-1,1)));
  v_1331.push_back(Diagonal(Point3D(-1,-1,1),Point3D(1,1,1)));
  v_1331.push_back(Diagonal(Point3D(1,1,1),Point3D(-1,1,-1)));
  v_1331.push_back(Diagonal(Point3D(1,1,1),Point3D(1,-1,-1)));
  v_1331.push_back(Diagonal(Point3D(-1,1,-1),Point3D(1,-1,-1)));

  v_2060.push_back(Diagonal(Point3D(-1,-1,-1),Point3D(-1,1,1)));
  v_2060.push_back(Diagonal(Point3D(-1,-1,-1),Point3D(1,-1,1)));
  v_2060.push_back(Diagonal(Point3D(-1,1,1),Point3D(1,-1,1)));
  v_2060.push_back(Diagonal(Point3D(-1,1,-1),Point3D(1,-1,-1)));
  v_2060.push_back(Diagonal(Point3D(-1,1,-1),Point3D(1,1,1)));
  v_2060.push_back(Diagonal(Point3D(1,-1,-1),Point3D(1,1,1)));

  v_2222.push_back(Diagonal(Point3D(-1,-1,-1),Point3D(1,1,-1)));
  v_2222.push_back(Diagonal(Point3D(-1,-1,1),Point3D(1,1,1)));
  v_2222.push_back(Diagonal(Point3D(-1,-1,1),Point3D(-1,1,-1)));
  v_2222.push_back(Diagonal(Point3D(-1,-1,1),Point3D(1,-1,-1)));
  v_2222.push_back(Diagonal(Point3D(1,1,1),Point3D(-1,1,-1)));
  v_2222.push_back(Diagonal(Point3D(1,1,1),Point3D(1,-1,-1)));

  v_4004.push_back(Diagonal(Point3D(-1,-1,1),Point3D(-1,1,-1)));
  v_4004.push_back(Diagonal(Point3D(-1,-1,1),Point3D(1,-1,-1)));
  v_4004.push_back(Diagonal(Point3D(-1,1,-1),Point3D(1,1,1)));
  v_4004.push_back(Diagonal(Point3D(1,-1,-1),Point3D(1,1,1)));
  v_4004.push_back(Diagonal(Point3D(-1,-1,1),Point3D(1,1,1)));
  v_4004.push_back(Diagonal(Point3D(-1,1,-1),Point3D(1,-1,-1)));
  // Gena stop
}

const vector<Diagonal>& EtalonDiags::getDiagsByType(Type type) {
  if (T_0602==type) return v_0602;
  if (T_1331==type) return v_1331;
  if (T_2060==type) return v_2060;
  if (T_2222==type) return v_2222;
  if (T_4004==type) return v_4004;
  cerr << "Wrong type\n";
  throw ;
}

const vector<SimplexModel>& EtalonDiags::getSimplexByType(Type type) {
  if (T_0602==type) return m_0602;
  if (T_1331==type) return m_1331;
  if (T_2060==type) return m_2060;
  if (T_2222==type) return m_2222;
  if (T_4004==type) return m_4004;
  cerr << "Wrong type\n";
  throw ;
}
