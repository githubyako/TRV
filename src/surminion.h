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
  bool m_vaChemin;
  unsigned int m_id;
public:
  SurMinion(std::vector<Minion*> const & _minions);
  void mutate(int numMinion, unsigned int _nbAjouts, float _ratioSupprs,float _ratioModifs);
  void mutateElite(int numMinion, unsigned int _nbAjouts,float _ratioModifs);
  void addMinion(Minion* _minion);
  bool getVaChemin() const;
  float const & getFitness() const;
  std::vector<Minion*> & getMinions();
  unsigned int getNumberMinions() const;
  Minion* getMinion(unsigned int _pairNumber);
  unsigned int getID() const;
  
  inline bool operator< (const SurMinion& _m2){ 
    if((m_vaChemin && _m2.getVaChemin()) || (!m_vaChemin && !_m2.getVaChemin())){
      return (m_fitness<_m2.getFitness());
    }else if(!m_vaChemin){
      return 0;
    }else{
      return 1;
    }
  }

  void setFitness(float _fitness);
  void setVaChemin(bool _vaChemin);
  void setMinions( std::vector<Minion*> const & _minions);
};

#endif
