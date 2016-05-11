#include "minion.h"
unsigned int Minion::m_incrID=0;

Minion::Minion(const std::vector< std::pair< bool, bool > *>& _genome):m_genome(_genome)
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
//   std::cout << "______________________________" << std::endl;
//   std::cout << "Minion avant mutate | id : " << m_id << " | taille : " << m_genome.size() << std::endl;
//   std::cout << "*******************" << std::endl;
  if(!m_vaChemin){
    unsigned int nbsupprs = (unsigned int)(ceil(_nbAjouts * _ratioSupprs));
    if(nbsupprs < m_genome.size()){
//       std::cout << "Taille avant suppression : " << m_genome.size() << std::endl;
      for(unsigned int i=1;i<nbsupprs;++i){													// suppressions
// 	std::cout << "suppression " << i << "sur " << nbsupprs << ", genome size =  " << m_genome.size() << std::endl;
	      unsigned int pos = rand() % m_genome.size();
	      std::swap(m_genome.at(pos),m_genome.back());
	      m_genome.pop_back();
      }
    }
//     std::cout << "Taille après suppression : " << m_genome.size() << std::endl;
    unsigned int nbmodifs = (unsigned int)(m_genome.size() * _ratioModifs);
    for(unsigned int i=0;i<nbmodifs;++i){  // modifications
      
      m_genome.at(rand() % m_genome.size()) = new std::pair<bool,bool>(rand()%2,rand()%2);
    }
//     std::cout << "Taille après modification : " << m_genome.size() << std::endl;
    for(unsigned int i=0;i<_nbAjouts;++i){													// modifications
	    m_genome.push_back(new std::pair<bool,bool>(rand()%2,rand()%2));
    }
/*    std::cout << "Taille après ajout : " << m_genome.size() << std::endl;
    std::cout << "*******************" << std::endl;
    std::cout << "Minion après mutate | id : " << m_id << " | taille : " << m_genome.size() << std::endl;*/
/*  
    unsigned int originX = m_sommetfinal->getX();
    unsigned int originY = m_sommetfinal->getY();
    unsigned int cibleX = _cible->getX();
    unsigned int cibleY = _cible->getY();
    bool a = cibleX < originX;
    bool b = cibleX == originX;
    bool c = 1-a-b;
    bool d = cibleY < originY;
    bool e = cibleY == originY;
    bool f = 1-d-e;
    std::vector<std::pair<bool, bool> > ajout_astar = Map::m_map->A_star_GA(m_sommetfinal, ((originX+3*((a-c)*(1-e)+2*(c-a)))*Map::get_m_h()+(originY+3*((d-f)*(1-b)+2*(e-a-b-c+2*f)))), nullptr);
    m_genome.insert(m_genome.begin(), ajout_astar.begin(), ajout_astar.end());*/
  }else{
//     std::cout << "vachemin modifié" << std::endl;
//     if(1/((rand()%9)+1)>=_ratioModifs){
      unsigned int pos1=rand()%(m_genome.size()),pos2=rand()%(m_genome.size());
      bool firstbool=rand()%2,secondbool=rand()%2;
	// 1: introduction de 2 déplacements de direction opposées
       m_genome.insert(m_genome.begin()+pos1,new std::pair<bool,bool>(firstbool,secondbool));
       m_genome.insert(m_genome.begin()+pos2,new std::pair<bool,bool>(!firstbool,secondbool));
      // 3: permutation de 2 déplacements aléatoires, suppression si elles sont opposées
      unsigned int pos3=rand()%m_genome.size(),pos4=(rand()%(m_genome.size()-1))+1;
      if(m_genome.at(pos3)->first!=m_genome.at(pos4)->first && m_genome.at(pos3)->second==m_genome.at(pos4)->second)
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
	for(unsigned int i=0;i<_nbAjouts;++i){													// modifications
		m_genome.push_back(new std::pair<bool,bool>(rand()%2,rand()%2));
	}
  }
  else {

      unsigned int pos1=rand()%m_genome.size(),pos2=rand()%m_genome.size();
      bool firstbool=rand()%2,secondbool=rand()%2;
	// 1: introduction de 2 déplacements de direction opposées
       m_genome.insert(m_genome.begin()+pos1,new std::pair<bool,bool>(firstbool,secondbool));
       m_genome.insert(m_genome.begin()+pos2,new std::pair<bool,bool>(!firstbool,secondbool));
      
      // 3: permutation de 2 déplacements aléatoires, suppression si elles sont opposées
      unsigned int pos3=rand()%m_genome.size(),pos4=(rand()%(m_genome.size()-1))+1;
      if(m_genome.at(pos3)->first!=m_genome.at(pos4)->first && m_genome.at(pos3)->second==m_genome.at(pos4)->second)
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