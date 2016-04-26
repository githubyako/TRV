#ifndef MINION_H
#define MINION_H
#include <vector>
#include "case.h"
class Minion{
private:
  std::vector<std::pair<bool,bool> > m_genome;
  float m_fitness;
  bool m_vaChemin;
public:
  Minion(std::vector<std::pair<bool,bool> > const & _genome);
  void mutate(unsigned int _nbAjouts, float _ratioSupprs,float _ratioModifs);
  void mutateElite(unsigned int _nbAjouts);
  
  
  bool getVaChemin() const;
  float const & getFitness() const;
  std::vector<std::pair<bool,bool> > const & getGenome() const;
  unsigned int getGenomeSize() const;
    std::pair< bool, bool >* getChromosome(unsigned int _pairNumber) const;
  
  inline bool operator< (const Minion& _m2){ return m_fitness<_m2.getFitness();}

  void setFitness(float _fitness);
  void setVaChemin(bool _vaChemin);
  
};

#endif