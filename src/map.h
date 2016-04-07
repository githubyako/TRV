#ifndef MAP_H
#define MAP_H
#include <map>
#include "case.h"
#include "terrain.h"
#include "agent.h"
#include "unite.h"

class Map{
private:
  static Map* m_map;
  int m_w,m_h;
  std::map<int, Case*> m_sommets;
  std::vector<Terrain*> m_terrains;
  std::vector<Agent*> m_agents;
  std::vector<Unite*> m_unites;
  std::vector<Contrainte*> m_contrainteNames;
  Map();
  Map(Map const & _map);
  Map( int _w,  int _h); 
public:
  static Map* create(int _w, int _h);
  void addTerrain(std::string const & _type, std::vector<std::pair<std::string, float> > _contraintes_defaut);
  void addTerrain(std::string const & _type, std::vector<std::pair<std::string, float> > _contraintes_defaut, bool _obstacle);
  void addUnite(std::string const & _type, std::vector< std::pair<Terrain*,float> > _vitesse_d,std::vector< std::pair<Contrainte*, float> > _consoContraintes);
  void addAgent(int _iden, int _x, int _y, std::string const &_unite);
  void addContrainte(const std::string& _contrainte);
  int get_m_w();
  int get_m_h();
  Case* get_Case(int _x, int _y);
  std::vector<Agent*> get_Agents();
  ~Map();
  
};


#endif
