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
  std::vector<Contrainte*> m_contraintes;
 
public:
  Map();
  Map(Map const & _map);
  Map( int _w,  int _h);
  static Map* create(int _w, int _h);
  void addTerrain(std::string const & _type, std::vector<std::pair<std::string const &, float> > & _contraintes_defaut);
  void addTerrain(std::string const & _type, std::vector<std::pair<std::string const &, float> > & _contraintes_defaut, bool _obstacle);
  void addUnite(const std::string& _type, std::vector< std::pair< std::string const&, float > >& _vitesse_d, 
		std::vector< std::pair< std::string const&, float > >& _consoContraintes);
  void addAgent(int _iden, int _x, int _y, std::string const &_unite);
  void addContrainte(std::string const& _contrainte);
  void move_agent(int id, int x, int y);
  void suppr_agent(int id);
  int get_m_w() const;
  int get_m_h() const;
  Case* get_Case(int _x, int _y) const;
  Agent* get_Agent(int id) const;
  Terrain* get_Terrain(std::string const & _terrName) const;
  Contrainte * get_Contrainte(std::string const & _contrName) const;
  void set_Terrain(int _x, int _y, std::string const & _terrName);
  void set_Obstacle(int _x, int _y, int obst);
  ~Map();
  
};


#endif
