#ifndef ALGOGEN_H
#define ALGOGEN_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <set>

#include "minion.h"
#include "map.h"

class Algogen{
private:
  Map * m_map;
  Agent* m_agent;
  Case* m_cible;
  std::set<Minion*> m_pop;
  unsigned int m_popsize;
public:
  Algogen(Map * _map, unsigned int _popsize);
  std::vector<int> const & findPath(int _idAgent, int _caseCible);
  unsigned int fitness();
  
  ~Algogen();
};
#endif