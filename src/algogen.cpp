#include "algogen.h"

Algogen::Algogen(Map* _map, unsigned int _popsize):m_map(_map)
{
  
}

const std::vector< int >& Algogen::findPath(int _idAgent, int _caseCible)
{
  m_agent=m_map->get_Agent(_idAgent);
  m_cible=m_map->get_Case(_caseCible);
  int originX = m_agent->getCase()->getX();
  int originY = m_agent->getCase()->getY();
  
}

unsigned int Algogen::fitness()
{
  
}

Algogen::~Algogen()
{
  for (std::set<Minion*>::iterator it = m_pop.begin(); it !=  m_pop.end(); ++it){
    delete *it;
  }
}
