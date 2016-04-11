#include "case.h"
#include "str_exception.h"

// *************
// Constructeurs
// *************

Case::Case(int _x, int _y, int _somm, Terrain * _terrain)
:m_x(_x),m_y(_y),m_somm(_somm),m_terrain(_terrain)
{
  m_obstacle = _terrain->isObstacle();
  m_contraintes = _terrain->getContraintes();
}

Case::Case()
{}

Case::Case(const Case& _case)
{}

// ********
// Getteurs
// ********

float Case::getContrainte(Contrainte* _contrainte) const
{
  // On regarde si la contrainte existe dans le vecteur m_contraintes de la case
  for(unsigned int i=0;i<m_contraintes.size();++i){
    if(m_contraintes.at(i).first->getNom() ==_contrainte->getNom()){
      return m_contraintes.at(i).second;
    }
  }
  throw new str_exception("Contrainte '" + _contrainte->getNom() + "' non trouvée dans la case (" + std::to_string(m_x) + "," + std::to_string(m_y) + ").");
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

unsigned int Case::get_sommet() const
{
  return m_somm;
}


bool Case::isObstacle() const
{
  return m_obstacle;
}

// ********
// Setteurs
// ********

void Case::setContrainte(std::vector< std::pair< Contrainte*, float > > _contr)
{
  m_contraintes=_contr;
}


void Case::setContrainte(Contrainte* _contrainte,float _qte)
{
  bool foundContr=false;
  // On regarde si la contrainte existe déjà dans le vecteur m_contrainte de la case
  for(unsigned int i=0;i<m_contraintes.size();++i){
    if(m_contraintes.at(i).first==_contrainte){
      m_contraintes.at(i).second=_qte;
      foundContr=true;
    }
  }
  // Si non, on en la rajoute au vecteur
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
  m_obstacle = _terrain->isObstacle();
  m_terrain=_terrain;
}
