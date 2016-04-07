#include "case.h"
#include "str_exception.h"
Case::Case(int _x, int _y, int _somm, Terrain * _terrain)
:m_x(_x),m_y(_y),m_somm(_somm),m_terrain(_terrain)
{

}

Case::Case()
{

}

Case::Case(const Case& _case)
{

}


float Case::getContrainte(Contrainte const & _contrainte) const
{
  for(unsigned int i=0;i<m_contraintes.size();++i){
    if(m_contraintes.at(i).first==&_contrainte){
      return m_contraintes.at(i).second;
    }
  }
  throw new str_exception("Contrainte '" + _contrainte.getNom() + "' non trouvée dans la case (" + std::to_string(m_x) + "," + std::to_string(m_y) + ").");
}

const Terrain& Case::getTerrain() const
{
  return *m_terrain;
}

unsigned int Case::getX() const
{
  return m_x;
}

unsigned int Case::getY() const
{
  return m_y;
}

bool Case::isObstacle() const
{
  return m_obstacle;
}

void Case::setContrainte_obs(Contrainte* _contrainte,float _qte)
{
  bool foundContr=false;
  for(unsigned int i=0;i<m_contraintes.size();++i){
    if(m_contraintes.at(i).first==_contrainte){
      m_contraintes.at(i).second=_qte;
      foundContr=true;
    }
  }
  if(foundContr==false){
    m_contraintes.push_back(std::pair<Contrainte*,int>(_contrainte,_qte));
  }
}

void Case::setObstacle(bool _b)
{
  m_obstacle=_b;
}

void Case::setTerrain(Terrain* _terrain)
{
  m_terrain=_terrain;
}
