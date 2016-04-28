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

std::pair< bool, bool > & Minion::getChromosome(unsigned int _pairNumber)
{
	return m_genome.at(_pairNumber);
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
  }else{
    std::cout << "vachemin modifié" << std::endl;
    if(1/((rand()%9)+1)<=_ratioModifs){
	
      unsigned int pos1=rand()%m_genome.size(),pos2=rand()%m_genome.size();
      std::vector<std::pair<bool,bool> >::iterator it = m_genome.begin();
      bool firstbool=rand()%2,secondbool=rand()%2;
	// 1: introduction de 2 déplacements de direction opposées
  //     m_genome.insert(it+pos1,std::pair<bool,bool>(firstbool,secondbool));
  //     m_genome.insert(it+pos2,std::pair<bool,bool>(!firstbool,secondbool));
  //     
      // 3: permutation de 2 déplacements aléatoires, suppression si elles sont opposées
      unsigned int pos3=rand()%m_genome.size(),pos4=(rand()%(m_genome.size()-1))+1;
      if(m_genome.at(pos3).first!=m_genome.at(pos4).first && m_genome.at(pos3).second==m_genome.at(pos4).second){
	m_genome.erase(m_genome.begin()+pos3);
	m_genome.erase(m_genome.begin()+pos4-1);
      }else{
	std::iter_swap(m_genome.begin()+pos3,m_genome.begin()+pos4);
      }
    }
  }
}

void Minion::mutateElite(unsigned int _nbAjouts, float _ratioModifs)
{
  if(!m_vaChemin){
	for(unsigned int i=0;i<_nbAjouts;++i){													// modifications
		m_genome.push_back(std::pair<bool,bool>(rand()%2,rand()%2));
	}
  }else{
    if(1/((rand()%9)+1)<=_ratioModifs){

      std::cout << "vachemin modifié" << std::endl;
      unsigned int pos1=rand()%m_genome.size(),pos2=rand()%m_genome.size();
      std::vector<std::pair<bool,bool> >::iterator it = m_genome.begin();
      bool firstbool=rand()%2,secondbool=rand()%2;
	// 1: introduction de 2 déplacements de direction opposées
  //     m_genome.insert(it+pos1,std::pair<bool,bool>(firstbool,secondbool));
  //     m_genome.insert(it+pos2,std::pair<bool,bool>(!firstbool,secondbool));
  //     
      // 3: permutation de 2 déplacements aléatoires, suppression si elles sont opposées
      unsigned int pos3=rand()%m_genome.size(),pos4=(rand()%(m_genome.size()-1))+1;
      if(m_genome.at(pos3).first!=m_genome.at(pos4).first && m_genome.at(pos3).second==m_genome.at(pos4).second){
	m_genome.erase(m_genome.begin()+pos3);
	m_genome.erase(m_genome.begin()+pos4-1);
      }else{
	std::iter_swap(m_genome.begin()+pos3,m_genome.begin()+pos4);
      }
    }
  }
}