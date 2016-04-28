#include "minion.h"

Minion::Minion(const std::vector< std::pair< bool, bool > >& _genome):m_genome(_genome)
{
  m_vaChemin=false;
}

//					GETTERS/SETTERS

const std::vector< std::pair< bool, bool > >& Minion::getGenome() const
{
  return m_genome;
}

float const &  Minion::getFitness() const
{
  return m_fitness;
}

void Minion::setFitness(float _fitness)
{
  m_fitness=_fitness;
}

unsigned int Minion::getGenomeSize() const
{
	return m_genome.size();
}

std::pair< bool, bool >* Minion::getChromosome(unsigned int _pairNumber) const
{
	if(m_genome.size() > _pairNumber){
		return new std::pair<bool,bool>(m_genome.at(_pairNumber));
	}else return nullptr;
}

bool Minion::getVaChemin() const
{
  return m_vaChemin;
}

unsigned int Minion::getManhattan() const
{
  return m_manhattan;
}


void Minion::setVaChemin(bool _vaChemin)
{
  m_vaChemin = _vaChemin;
}

void Minion::setManhattan(unsigned int _manhattan)
{
  m_manhattan = _manhattan;
}

void Minion::setGenome(const std::vector< std::pair< bool, bool > >& _genome)
{
  m_genome = _genome;
}


// 					METHODES

void Minion::mutate(unsigned int _nbAjouts, float _ratioSupprs, float _ratioModifs)
{
  if(!m_vaChemin){
	unsigned int nbsupprs = (unsigned int)(m_genome.size() * _ratioSupprs);
	for(unsigned int i=0;i<nbsupprs;++i){													// suppressions
		std::swap(m_genome.at(i),m_genome.back());
		m_genome.pop_back();
	}
	
	unsigned int nbmodifs = (unsigned int)(m_genome.size() * _ratioModifs);
	for(unsigned int i=0;i<nbmodifs;++i){													// modifications
		m_genome.at(rand() % m_genome.size()) = std::pair<bool,bool>(rand()%2,rand()%2);
	}

	for(unsigned int i=0;i<_nbAjouts;++i){													// modifications
		m_genome.push_back(std::pair<bool,bool>(rand()%2,rand()%2));
	}
  }
}

void Minion::mutateElite(unsigned int _nbAjouts)
{
  if(!m_vaChemin){
	for(unsigned int i=0;i<_nbAjouts;++i){													// modifications
		m_genome.push_back(std::pair<bool,bool>(rand()%2,rand()%2));
	}
  }
}
