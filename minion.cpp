#include "minion.h"

Minion::Minion(const std::vector< std::pair< bool, bool > >& _genome):m_genome(_genome)
{
  
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



// 					METHODES

void Minion::mutate(float _ratioAjouts, float _ratioSupprs, float _ratioModifs)
{
	unsigned int nbsupprs = (unsigned int)(m_genome.size() * _ratioSupprs);
	for(unsigned int i=0;i<nbsupprs;++i){													// suppressions
		std::swap(m_genome.at(i),m_genome.back());
		m_genome.pop_back();
	}
	
	unsigned int nbmodifs = (unsigned int)(m_genome.size() * _ratioModifs);
	for(unsigned int i=0;i<nbmodifs;++i){													// modifications
		m_genome.at(rand() % m_genome.size()) = std::pair<bool,bool>(rand()%2,rand()%2);
	}
	
	unsigned int nbajouts = 4; //(unsigned int)(m_genome.size() * _ratioAjouts);
	for(unsigned int i=0;i<nbajouts;++i){													// modifications
		m_genome.push_back(std::pair<bool,bool>(rand()%2,rand()%2));
	}
}

void Minion::mutateElite(float _ratioAjouts)
{
	unsigned int nbajouts = 4; //(unsigned int)(m_genome.size() * _ratioAjouts)
	for(unsigned int i=0;i<nbajouts;++i){													// modifications
		m_genome.push_back(std::pair<bool,bool>(rand()%2,rand()%2));
	}
}
