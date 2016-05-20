#include "surminion.h"
unsigned int SurMinion::m_incrID=0;

SurMinion::SurMinion(std::vector<Minion*> const & _minions)
{
  for(unsigned int i =0; i<_minions.size();++i){
    m_minions.push_back(new Minion(*(_minions.at(i))));
  }
  m_vaChemin=false;
  m_id=m_incrID++;
}

SurMinion::~SurMinion()
{
  for (unsigned int i =0; i<m_minions.size(); ++i)
    delete m_minions.at(i);
}


void SurMinion::addMinion(Minion* _minion)
{
  m_minions.push_back(_minion);
}

void SurMinion::removeMinion(unsigned int _minionNumber)
{
  delete *(m_minions.begin()+_minionNumber);
  m_minions.erase(m_minions.begin()+_minionNumber);
}



const float& SurMinion::getFitness() const
{
  return m_fitness;
}

std::vector< Minion* >& SurMinion::getMinions()
{
  return m_minions;
}

unsigned int SurMinion::getNumberMinions() const
{
  return m_minions.size();
}

unsigned int SurMinion::getID() const
{
  return m_id;
}

Minion* SurMinion::getMinion(unsigned int _pairNumber)
{
  return m_minions.at(_pairNumber);
}

unsigned int SurMinion::getVaChemin() const
{
  return m_vaChemin;
}

void SurMinion::setFitness(float _fitness)
{
  m_fitness = _fitness;
}

void SurMinion::setMinions(std::vector<Minion*> const & _minions)
{
  m_minions=_minions;
}

void SurMinion::setVaChemin(unsigned int _vaChemin)
{
  m_vaChemin=_vaChemin;
}

void SurMinion::mutate(int numMinion, unsigned int _nbAjouts, float _ratioSupprs, float _ratioModifs)
{
  m_minions.at(numMinion)->mutate(_nbAjouts,_ratioSupprs,_ratioModifs);
}

void SurMinion::mutateElite(int numMinion, unsigned int _nbAjouts, float _ratioModifs)
{
  m_minions.at(numMinion)->mutateElite(_nbAjouts,_ratioModifs);
}
