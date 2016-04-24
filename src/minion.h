#ifndef MINION_H
#define MINION_H
#include <vector>
#include "case.h"
class Minion{
private:
  std::vector<std::pair<bool,bool> > m_genome;
  float m_fitness;
public:
  Minion(std::vector<std::pair<bool,bool> > const & _genome);
  void mutate(float _ratioAjouts, float _ratioSupprs,float _ratioModifs);
  void mutateElite(float _ratioAjouts);
  
  
  float const & getFitness() const;
  std::vector<std::pair<bool,bool> > const & getGenome() const;
  unsigned int getGenomeSize() const;
    std::pair< bool, bool >* getChromosome(unsigned int _pairNumber) const;
  
  inline bool operator< (const Minion& _m2){ return m_fitness<_m2.getFitness();}

  void setFitness(float _fitness);
};

#endif