#ifndef GENETIQUETV
#define GENETIQUETV
#include <vector>
#include <algorithm>
#include "case.h"
#include "map.h"
#include "deplacement.h"
#include <iostream>
class genetiqueTV {
private:
  std::vector<deplacement *> m_population;
  Map * m_map;
  Agent * m_agent;
  unsigned int m_depart;
  unsigned int m_arrivee;
public:
  genetiqueTV(Map* map, Agent* agent, int arrivee);
//   const std::vector<Case*> recherche_chemin();
};
#endif