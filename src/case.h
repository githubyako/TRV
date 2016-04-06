#ifndef CASE_H
#define CASE_H
#include <map>
#include "terrain.h"
#include "contrainte.h"
#include <vector>
class Case{
  
private:
  unsigned int m_x,m_y;
  std::vector<std::pair<Contrainte*,float> >m_contraintes;
  bool m_obstacle;
  unsigned int m_somm;
  Terrain * m_terrain;
  
  static unsigned int id_somm;
  
  void setObstacle(bool _b);
  void setTerrain(Terrain* _terrain);
  void setContrainte_obs(Contrainte* _contrainte,float _qte);
  Case();
  Case(Case const & _case);
public:
  Case(int _x, int _y, int _somm, Terrain * _terrain);
  unsigned int getX() const;
  unsigned int getY() const;
  float getContrainte(Contrainte const & contrainte) const;
  const Terrain & getTerrain() const;
  bool isObstacle() const;
};
#endif