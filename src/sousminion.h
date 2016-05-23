#ifndef SOUSMINION_H
#define SOUSMINION_H
#include <vector>
#include <iostream>

#include "case.h"
#include "minion.h"

class SousMinion{
private:
  int m_idAgent;
  std::vector<std::pair<bool,bool> *> m_genomeDebut;
  std::vector<std::pair<bool,bool> *> m_genomeLeader;
  const Unite* m_unite;
  unsigned int m_leader;
  int m_caseSource,m_caseCible;
  
public:
  SousMinion(int _idAgent, const std::vector< std::pair< bool, bool >* >& _genome, const Unite* _unite, int _caseCible);
  ~SousMinion();
  
  std::vector<std::pair<bool,bool> *> const & getGenomeDebut() const;
  std::vector<std::pair<bool,bool> *> const & getGenomeLeader() const;
  unsigned int getGenomeSize() const;
  std::pair< bool, bool > * getChromosome(unsigned int _pairNumber);
  int getID() const;
  unsigned int getLeader() const;
  int getCaseSource() const;
  int getCaseCible() const;
  const Unite* getUnite() const;
  
  void setGenomeDebut( std::vector<std::pair<bool,bool> *> const & _genome);
  void setGenomeLeader( std::vector<std::pair<bool,bool> *> const & _genome);
  void setLeader( unsigned int _leader);
  void setCaseSource(int _sommet);
  void popfront();
  void addChrom(std::pair<bool,bool>* _chrom);
};

#endif