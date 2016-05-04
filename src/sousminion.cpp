#include "sousminion.h"

SousMinion::SousMinion(int _idAgent, const std::vector< std::pair< bool, bool >* >& _genome)
:m_idAgent(_idAgent),m_genome(_genome)
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

const Minion* SousMinion::getLeader() const
{
  return m_leader;
}

void SousMinion::setLeader(Minion* _leader)
{
  m_leader = _leader;
}


void SousMinion::setGenome(const std::vector< std::pair< bool, bool >* >& _genome)
{
  m_genome = _genome;
}

unsigned int SousMinion::getID() const
{
  return m_idAgent;
}
