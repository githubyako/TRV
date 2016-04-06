#ifndef MAP_H
#define MAP_H
#include <map>
#include "case.h"
#include "terrain.h"
#include "agent.h"
#include "unite.h"

class Map{
private:
//   std::map<unsigned int, Case*> m_map; A MODIFIER
  std::vector<Terrain*> m_terrains;
  std::vector<Agent*> m_agents;
  std::vector<Unite*> m_unites;
  std::vector<std::string> m_contrainteNames;
  Map();
  Map(Map const & _map);
  
public:
//   Map(unsigned int _w, unsigned int _h); A MODIFIER
  ~Map();
  
};


#endif