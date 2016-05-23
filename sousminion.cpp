#include "sousminion.h"

SousMinion::SousMinion(int _idAgent, const std::vector< std::pair< bool, bool >* >& _genome, int _caseCible)
:m_idAgent(_idAgent), m_genomeDebut(_genome),m_caseCible(_caseCible)
{
  
}

SousMinion::~SousMinion()
{
  for (unsigned int i=0; i<m_genomeDebut.size(); ++i)
  {
    delete m_genomeDebut.at(i);
  }
  for (unsigned int i=0; i<m_genomeLeader.size(); ++i)
  {
    delete m_genomeLeader.at(i);
  }
}

std::pair< bool, bool >* SousMinion::getChromosome(unsigned int _pairNumber)
{
  if(m_genomeDebut.size()>_pairNumber){
    std::cout << "genome debu " << m_genomeDebut.size() << std::endl;
    return m_genomeDebut.at(_pairNumber);
  }else{
    std::cout << "genome leaderu" << std::endl;
    return m_genomeLeader.at(_pairNumber-m_genomeDebut.size());
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

int SousMinion::getCaseCible() const
{
  return m_caseCible;
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
  m_genomeLeader.clear();
  for(unsigned int i=0;i<_genome.size();++i){
    std::cout << "avant : " << _genome.at(i)->first << ", " << _genome.at(i)->second;
    m_genomeLeader.push_back(new std::pair<bool,bool>(*_genome.at(i)));
  }
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
  if(m_genomeDebut.size()==0){
    std::cout << std::endl << std::endl << "Erasing leader chromz" << std::endl;
    std::cout << "genomeleader size = " << m_genomeLeader.size() << ", genome debut size = " << m_genomeDebut.size() << std::endl;
    m_genomeLeader.erase(m_genomeLeader.begin());
  }else{
    m_genomeDebut.erase(m_genomeDebut.begin());
  }
}

void SousMinion::addChrom(std::pair< bool, bool >* _chrom)
{
  m_genomeLeader.push_back(new std::pair<bool,bool>(*_chrom));
}
