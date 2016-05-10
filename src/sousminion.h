#ifndef SOUSMINION_H
#define SOUSMINION_H
#include <vector>
#include <iostream>

#include "case.h"
#include "minion.h"

class SousMinion{
private:
  int m_idAgent;
  std::vector<std::pair<bool,bool> *> m_begin;
  std::vector<std::pair<bool,bool> *> m_genome;
  Minion* m_leader;
  
public:
  SousMinion(int _idAgent, const std::vector< std::pair< bool, bool >* >& _begin, const std::vector< std::pair< bool, bool >* >& _genome);
  ~SousMinion();
  
  std::vector<std::pair<bool,bool> *> const & getGenome() const;
  unsigned int getGenomeSize() const;
  std::pair< bool, bool > * getChromosome(unsigned int _pairNumber);
  int getID() const;
  Minion * getLeader() const;
  
  void setGenome( std::vector<std::pair<bool,bool> *> const & _genome);
  void setLeader(Minion * _leader);
};

#endif