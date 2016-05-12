#ifndef SOUSMINION_H
#define SOUSMINION_H
#include <vector>
#include <iostream>

#include "case.h"
#include "minion.h"

class SousMinion{
private:
  int m_idAgent;
  std::vector<std::pair<bool,bool> *> m_genome;
  unsigned int m_leader;
  int m_caseSource;
  
public:
  SousMinion(int _idAgent, const std::vector< std::pair< bool, bool >* >& _genome);
  ~SousMinion();
  
  std::vector<std::pair<bool,bool> *> const & getGenome() const;
  unsigned int getGenomeSize() const;
  std::pair< bool, bool > * getChromosome(unsigned int _pairNumber);
  int getID() const;
  unsigned int getLeader() const;
  int getCaseSource() const;
  
  void setGenome( std::vector<std::pair<bool,bool> *> const & _genome);
  void setLeader( unsigned int _leader);
  void setCaseSource(int _sommet);
};

#endif