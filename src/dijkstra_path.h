#ifndef DIJKSTRA_PATH
#define DIJKSTRA_PATH
#include <vector>
#include <algorithm>
#include "case.h"
#include "map.h"
#include "agent.h"
#include <iostream>
class Map;
class Dijkstra_path{
private:
  Map * m_map;
  std::map<int, float> m_couts;
  std::vector<int> m_chemin;
  int m_casenb;
  float totalcost;
  Case* lol,*m_casecible;
  bool fini;
//   Dijkstra_path();
//   Dijkstra_path(Dijkstra_path const & _dp);
public:
  Dijkstra_path(Map * _map);
  std::vector<int> const & findPath(int _idAgent, int _caseCible);
  Case* recurse(int _idAgent, Case const* _case);
};
#endif