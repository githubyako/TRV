#ifndef SURMINION_H
#define SURMINION_H
#include <vector>
#include <iostream>

#include "minion.h"
// #include "map.h"

class SurMinion{
private:
  static unsigned int m_incrID;
  std::vector<Minion*> m_minions;
  float m_fitness;
  unsigned int m_vaChemin;
  unsigned int m_id;
public:
  SurMinion(std::vector<Minion*> const & _minions);
  ~SurMinion();
  void mutate(int numMinion, unsigned int _nbAjouts, float _ratioSupprs,float _ratioModifs);
  void mutateElite(int numMinion, unsigned int _nbAjouts,float _ratioModifs);
  void addMinion(Minion* _minion);
  void removeMinion(unsigned int _minionNumber);
  unsigned int getVaChemin() const;
  float const & getFitness() const;
  std::vector<Minion*> & getMinions();
  unsigned int getNumberMinions() const;
  Minion* getMinion(unsigned int _pairNumber);
  unsigned int getID() const;

  void setFitness(float _fitness);
  void setVaChemin(unsigned int _vaChemin);
  void setMinions( std::vector<Minion*> const & _minions);
};

#endif