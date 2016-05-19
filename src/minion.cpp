#include "minion.h"
unsigned int Minion::m_incrID=0;

Minion::Minion(const std::vector< std::pair< bool, bool >* >& _genome, int _idAgent):m_idAgent(_idAgent), m_genome(_genome)
{
  m_vaChemin=false;
  m_id=m_incrID++;
}

Minion::Minion(const Minion& _minion)
:m_genome(_minion.getGenome()),m_fitness(_minion.getFitness()),m_vaChemin(_minion.getVaChemin()),m_manhattan(_minion.getManhattan()),m_sommetfinal(_minion.getSF())
{
  m_vaChemin=false;
  m_id=m_incrID++;
}


Minion::~Minion()
{
  for(unsigned int i=0;i<m_genome.size();i++){
    delete m_genome.at(i);
  }
}


//					GETTERS/SETTERS

const std::vector< std::pair< bool, bool > *>& Minion::getGenome() const
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

std::pair< bool, bool > * Minion::getChromosome(unsigned int _pairNumber)
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

unsigned int Minion::getID() const
{
  return m_id;
}

unsigned int Minion::getSF() const
{
  return m_sommetfinal;
}

int Minion::getIDAgent() const
{
  return m_idAgent;
}


void Minion::setVaChemin(bool _vaChemin)
{
  m_vaChemin = _vaChemin;
}

void Minion::setManhattan(unsigned int _manhattan)
{
  m_manhattan = _manhattan;
}

void Minion::setGenome(const std::vector< std::pair< bool, bool > *>& _genome)
{
  m_genome = _genome;
}

void Minion::setSommetFinal(unsigned int _sommet)
{
  m_sommetfinal=_sommet;
}


// 					METHODES

void Minion::mutate(unsigned int _nbAjouts, float _ratioSupprs, float _ratioModifs)
{
  if(!m_vaChemin){
    unsigned int nbsupprs = (unsigned int)(ceil(_nbAjouts * _ratioSupprs));
    if(nbsupprs < m_genome.size()){
      for(unsigned int i=1;i<nbsupprs;++i){
	      unsigned int pos = rand() % m_genome.size();
	      std::swap(m_genome.at(pos),m_genome.back());
	      m_genome.pop_back();
      }
    }
    unsigned int nbmodifs = (unsigned int)(m_genome.size() * _ratioModifs);
    for(unsigned int i=0;i<nbmodifs;++i){  // modifications
      
      m_genome.at(rand() % m_genome.size()) = new std::pair<bool,bool>(rand()%2,rand()%2);
    }
    for(unsigned int i=0;i<_nbAjouts;++i){
      m_genome.push_back(new std::pair<bool,bool>(rand()%2,rand()%2));
    }
  }else{
      unsigned int pos1=rand()%(m_genome.size()),pos2=rand()%(m_genome.size());
      bool firstbool=rand()%2,secondbool=rand()%2;
       m_genome.insert(m_genome.begin()+pos1,new std::pair<bool,bool>(firstbool,secondbool));
       m_genome.insert(m_genome.begin()+pos2,new std::pair<bool,bool>(!firstbool,secondbool));
      unsigned int pos3=rand()%m_genome.size(),pos4=(rand()%(m_genome.size()-1))+1;
      if((m_genome.at(pos3) != nullptr && m_genome.at(pos4) != nullptr ) && m_genome.at(pos3)->first!=m_genome.at(pos4)->first && m_genome.at(pos3)->second==m_genome.at(pos4)->second)
      {
	if (pos3 < pos4)
	{
	  delete *(m_genome.begin()+pos4);
	  delete *(m_genome.begin()+pos3);
	  m_genome.erase(m_genome.begin()+pos4);
	  m_genome.erase(m_genome.begin()+pos3);
	}
	else if(pos3 > pos4)
	{
	  delete *(m_genome.begin()+pos3);
	  delete *(m_genome.begin()+pos4);
	  m_genome.erase(m_genome.begin()+pos3);
	  m_genome.erase(m_genome.begin()+pos4);
	}
      }
      else{
	std::iter_swap(m_genome.begin()+pos3,m_genome.begin()+pos4);
      }
//     }
  }
}

void Minion::mutateElite(unsigned int _nbAjouts, float _ratioModifs)
{
  if(!m_vaChemin){
	for(unsigned int i=0;i<_nbAjouts;++i){
		m_genome.push_back(new std::pair<bool,bool>(rand()%2,rand()%2));
	}
  }
  else {
      unsigned int pos1=rand()%m_genome.size(),pos2=rand()%m_genome.size();
      bool firstbool=rand()%2,secondbool=rand()%2;
      m_genome.insert(m_genome.begin()+pos1,new std::pair<bool,bool>(firstbool,secondbool));
      m_genome.insert(m_genome.begin()+pos2,new std::pair<bool,bool>(!firstbool,secondbool));
      unsigned int pos3=rand()%m_genome.size(),pos4=(rand()%(m_genome.size()-1))+1;
      if((m_genome.at(pos3) != nullptr && m_genome.at(pos4) != nullptr ) && m_genome.at(pos3)->first!=m_genome.at(pos4)->first && m_genome.at(pos3)->second==m_genome.at(pos4)->second)
      {
	if (pos3 < pos4)
	{
	  delete *(m_genome.begin()+pos4);
	  delete *(m_genome.begin()+pos3);
	  m_genome.erase(m_genome.begin()+pos4);
	  m_genome.erase(m_genome.begin()+pos3);
	}
	else if(pos3 > pos4)
	{
	  delete *(m_genome.begin()+pos3);
	  delete *(m_genome.begin()+pos4);
	  m_genome.erase(m_genome.begin()+pos3);
	  m_genome.erase(m_genome.begin()+pos4);
	}
      }
      else{
	std::iter_swap(m_genome.begin()+pos3,m_genome.begin()+pos4);
      }
    }
}

void Minion::popfront()
{
  m_genome.erase(m_genome.begin());
}

