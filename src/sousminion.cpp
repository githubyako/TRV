#include "sousminion.h"

SousMinion::SousMinion(int _idAgent, const std::vector< std::pair< bool, bool >* >& _genome)
:m_idAgent(_idAgent), m_genomeDebut(_genome)
{
  
}

SousMinion::~SousMinion()
{

}

std::pair< bool, bool >* SousMinion::getChromosome(unsigned int _pairNumber)
{
  if(m_genomeDebut.size()>=_pairNumber){
    return m_genomeDebut.at(_pairNumber);
  }else{
    return m_genomeLeader.at(_pairNumber);
  }
}

const std::vector< std::pair< bool, bool >* >& SousMinion::getGenomeDebut() const
{
  return m_genomeDebut;
}

const std::vector< std::pair< bool, bool >* >& SousMinion::getGenomeLeader() const
{
  return m_genomeLeader;
}


unsigned int SousMinion::getGenomeSize() const
{
  return m_genomeDebut.size();
}

 unsigned int SousMinion::getLeader() const
{
  return m_leader;
}

int SousMinion::getCaseSource() const
{
  return m_caseSource;
}


void SousMinion::setLeader( unsigned int _leader)
{
  m_leader = _leader;
}

void SousMinion::setGenomeDebut(const std::vector< std::pair< bool, bool >* >& _genome)
{
  m_genomeDebut = _genome;
}


void SousMinion::setGenomeLeader(const std::vector< std::pair< bool, bool >* >& _genome)
{
  m_genomeLeader = _genome;
}


void SousMinion::setCaseSource(int _sommet)
{
  m_caseSource = _sommet;
}


int SousMinion::getID() const
{
  return m_idAgent;
}

void SousMinion::popfront()
{
  m_genomeLeader.erase(m_genomeLeader.begin());
}
