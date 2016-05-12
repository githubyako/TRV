#include "sousminion.h"

SousMinion::SousMinion(int _idAgent, const std::vector< std::pair< bool, bool >* >& _genome)
:m_idAgent(_idAgent), m_genome(_genome)
{
  
}

SousMinion::~SousMinion()
{

}

std::pair< bool, bool >* SousMinion::getChromosome(unsigned int _pairNumber)
{
  return m_genome.at(_pairNumber);
}

const std::vector< std::pair< bool, bool >* >& SousMinion::getGenome() const
{
  return m_genome;
}

unsigned int SousMinion::getGenomeSize() const
{
  return m_genome.size();
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


void SousMinion::setGenome(const std::vector< std::pair< bool, bool >* >& _genome)
{
  m_genome = _genome;
}

void SousMinion::setCaseSource(int _sommet)
{
  m_caseSource = _sommet;
}


int SousMinion::getID() const
{
  return m_idAgent;
}
