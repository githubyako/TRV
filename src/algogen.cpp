#include "algogen.h"

Algogen::Algogen(int map_w, int map_h, const std::map< int, Case* >* _sommets, unsigned int _popsize, float _manhattanImportance, float _mutationRatio, float _popToMutate, float _ratioAjouts, float _ratioSupprs, float _ratioModifs, float _ratioElitism, float _cullRatio, unsigned int _nbkids):
m_ratioElitism(_ratioElitism)
{
  std::srand(std::time(0));
  if(0>_manhattanImportance || 0>_mutationRatio || 0>_popToMutate || 0>_ratioAjouts || 0>_ratioSupprs || 0>_ratioModifs || 0>_cullRatio
	  || _manhattanImportance>1 || _mutationRatio>1 || _popToMutate>1 || _ratioAjouts>1 || _ratioSupprs>1 || _ratioModifs>1 || _cullRatio>1){
	  std::cerr << "Erreur: les ratios doivent être compris entre 0 et 1 inclus" << std::endl;
	  throw str_exception("Erreur: les ratios doivent être compris entre 0 et 1 inclus");
  }else{
	  m_mapW = map_w;
	  m_mapH = map_h;
	  m_sommets = _sommets;
	  m_popsize=_popsize;
	  m_manhattanImportance=_manhattanImportance;
	  m_mutationRatio=_mutationRatio;
	  m_popToMutate=_popToMutate;
	  m_ratioAjouts=_ratioAjouts;
	  m_ratioSupprs=_ratioSupprs;
	  m_ratioModifs=_ratioModifs;
	  m_cullRatio=_cullRatio;
	  m_nbkids=_nbkids;
  }
  std::cout << "constructeur OK" << std::endl;
}

void Algogen::initPop(int _caseSource, int _caseCible)
{
  m_orig=m_sommets->at(_caseSource);
  m_cible=m_sommets->at(_caseCible);
  unsigned int originX = m_orig->getX();
  unsigned int originY = m_orig->getY();
    for(unsigned int i=0;i<8;i++){																// creation pop initiale
      std::vector<std::pair<bool,bool> > genome;			// ALEATOIRE ET COURT, A AMELIORER VIA ASTAR_GA
      for(int j=0;j<5;++j){
	bool bool1 = rand() % 2;
	bool bool2 = rand() % 2;
	genome.push_back(std::pair<bool,bool>(bool1,bool2));
      }
      m_pop.push_back(new Minion(genome));
    }
  std::cout << "initpop OK" << std::endl;
}

Algogen::~Algogen()
{
    for (std::vector<Minion*>::iterator it = m_pop.begin(); it !=  m_pop.end(); ++it) {
        delete *it;
    }
}

void Algogen::crossover(Minion* _parent0, Minion* _parent1, Minion* _parent2)
{
  unsigned int nbchrs=std::max(std::max(_parent0->getGenomeSize(),_parent1->getGenomeSize()),_parent2->getGenomeSize());
  unsigned int parent;
  for(unsigned int i=0;i<m_nbkids;){
    std::vector<std::pair<bool,bool> > kidgenome;
//     std::cout << "debut du for" << std::endl;
    for(unsigned int j=0;j<nbchrs;++j){
      parent = rand()%3;
      if(parent==0 && _parent0->getChromosome(j)!=nullptr){
	kidgenome.push_back(*(_parent0->getChromosome(j)));
      }else if(parent==1 && _parent1->getChromosome(j)!=nullptr){
	kidgenome.push_back(*(_parent1->getChromosome(j)));
      }else if(_parent2->getChromosome(j)!=nullptr){
	kidgenome.push_back(*(_parent2->getChromosome(j)));
      }
    }
    if(kidgenome.size()!=0){
      m_pop.push_back(new Minion(kidgenome));
      ++i;
    }
//     std::cout << "fin du for" << std::endl;
  }
}

void Algogen::cull()
{
    for (std::vector<Minion*>::iterator it = m_pop.begin(); it !=  m_pop.end();) { // suppression des individus rencontrant un obstacle
		if ((*it)->getFitness() == 0.0){
			std::swap(*it, m_pop.back());
			m_pop.pop_back();
		}else  ++it;

    }
    unsigned int finRange = (unsigned int)(m_pop.size()/5);
    unsigned int totalSupprs = (unsigned int)(finRange * m_cullRatio);
    unsigned int supprs=0;
    bool ded;
    while(supprs<totalSupprs){
	    for (std::vector<Minion*>::iterator it = m_pop.begin(); it !=  m_pop.end() - finRange;) {
		    ded = rand() % 2;
		    if(ded && supprs < totalSupprs){
			    std::swap(*it, m_pop.back());
			    m_pop.pop_back();
			    supprs++;
		}else ++it;
	    }
    }
}

void Algogen::mutatePop()
{
	int size = (int)(m_pop.size() * m_popToMutate);
	m_lowestElite = (unsigned int)(m_pop.size() * (1 - m_ratioElitism));
	bool elite;
	for (int i=0;i<size;i++) {
		unsigned int MinionToMutate = rand() % m_pop.size();
		elite = (MinionToMutate > m_lowestElite);
		if(elite){
			m_pop.at(MinionToMutate)->mutateElite(m_ratioAjouts);
		}else{
			m_pop.at(MinionToMutate)->mutate(m_ratioAjouts, m_ratioSupprs,m_ratioModifs);
		}
    }
}

void Algogen::evaluate(Minion* _minion)
{
	float fitness=0.0;
	std::vector< std::pair< bool, bool > > genome = _minion->getGenome();
	std::pair<bool,bool> error;
	unsigned int newx = (int)(m_orig->getX());
	unsigned int newy = (int)(m_orig->getY());
	bool defect = false;
	std::vector<int> vec;
	unsigned int sommet = (newx*m_mapH) + newy;
	for(std::vector< std::pair< bool, bool > >::iterator cit = genome.begin(); cit != genome.end(); ++cit){ // parcours du chemin pour détection d'obstacle
	  newx += (*cit).second*(1-(2*(*cit).first));
	  newy += (1 - (*cit).first) * (1-(2*(*cit).second));
	  sommet = (newx*m_mapH) + newy;
// 	  std::cout << newx << " " << newy << " " << sommet;
	  /* 
	  if((*cit).first == 0 && (*cit).second == 0){
	    newy++;
	  }else if((*cit).first == 0 && (*cit).second == 1){
	    newx++;
	  }else if((*cit).first == 1 && (*cit).second == 0){
	    newy--;
	  }else if((*cit).first == 1 && (*cit).second == 1){
	    newx--;
	  }*/
	  if (newx < 0 || newx > m_mapW-1 || newy < 0 || newy > m_mapH-1){
	    newx -= (*cit).second*(1-(2*(*cit).first));
	    newy -= (1 - (*cit).first) * (1-(2*(*cit).second));
	    cit=genome.erase(cit);
	    sommet = (newx*m_mapH) + newy;
	    cit--;
	  }
	  else if(m_sommets->at(sommet)->isObstacle()){
		  defect = true;
		  break;
	  }
	  else if ((std::find(vec.begin(), vec.end(), sommet) != vec.end()))
	  {
	    std::cout << sommet << std::endl;
	    int pos = std::distance(vec.begin(),std::find(vec.begin(), vec.end(), sommet));
	    vec.erase(vec.begin()+pos, vec.begin()+(cit-genome.begin())-1);
	    cit=genome.erase(genome.begin()+pos, cit-1);
	    cit--;
	  }
	  else if(sommet == m_cible->get_sommet()){
	    std::cout << "CHEMIN VERS LA CIBLE TROUVE !!!1§§11§1§" << std::endl;
	  }
// 	  std::cout << std::endl;
	}
	if(!defect){
// 	  std::cout << newx << " " << newy << std::endl;
	  int manhattan = abs((m_cible->getX() - m_sommets->at(sommet)->getX())) + abs((m_cible->getY() - m_sommets->at(sommet)->getY()));
// 	  std::cout << manhattan << std::endl;
	  fitness = 1 - ((((float)manhattan / (m_mapW + m_mapH)) * m_manhattanImportance) + (((float)genome.size() / (m_mapH * m_mapW )) * (1-m_manhattanImportance)));
// 	  std::cout << fitness << std::endl;
	  vec.push_back(sommet);
	}
	std::cout << " | " << _minion->getGenomeSize() << " | ";
	_minion->setFitness(fitness);
}


void Algogen::iterate()
{
    float totalfitness=0.0;
    for (std::vector<Minion*>::iterator it = m_pop.begin(); it !=  m_pop.end(); ++it) {
      evaluate(*it);																		// evaluation fitness
      totalfitness+=(*it)->getFitness();
    }
//     std::cout << "Fitness moyenne avant itération: " << totalfitness / m_pop.size() << std::endl;
    m_generationTotalFitness.push_back(totalfitness / m_pop.size());						// ajout au tableau de la fitness générale
    if(m_generationTotalFitness.back() > m_generationTotalFitness.back() - 1){				// Si la fitness générale s'améliore, diminution du taux de mutation
      m_ratioSupprs = m_ratioSupprs * 0.99;
      m_ratioModifs = m_ratioModifs * 0.99;
  // 		m_ratioAjouts = m_ratioAjouts * 0.99; ?? bonne ou mauvaise idée?
    }
    
    std::sort (m_pop.begin(), m_pop.end()); 												// tri
//     std::cout << "tri ok, nettoyage" << std::endl;
    cull();																					// nettoyage
//     std::cout << "nettoyage ok, crossover" << std::endl;
    m_lowestElite = (unsigned int)(m_pop.size() * (1 - m_ratioElitism));
    Minion *m1=nullptr, *m2=nullptr, *m3=nullptr;
//     std::cout << "lol 1" << std::endl;
    while(m_pop.size()<m_popsize){															// reproduction par rank selection exponentielle tant que la population n'a pas atteint m_popsize
//       std::cout << "lol 2" << std::endl;
      unsigned int rank = 1;																// création d'un couple:
      for (int i = m_pop.size()-1;i>=0;i--){										// probabilité de sélection: 1/2 pour le meilleur individu, 1/4, pour le suivant, 1/8 pour le 3me...
// 	std::cout << "lol 2.5 " << m_pop.size() << " " << (unsigned int)(((1/(pow(2,rank))) * (float)m_pop.size())) << std::endl;
	if(rand()%m_pop.size() < (unsigned int)(((1/(pow(2,rank))) * (float)m_pop.size()))){
// 	  std::cout << "rentré dans le if " << std::endl;
	  if(m1==nullptr) {m1=m_pop.at(i);
	  }else if(m2==nullptr && m_pop.at(i)!=m1) {m2=m_pop.at(i);
	  }else if(m_pop.at(i)!=m1 && m_pop.at(i)!=m2){m3=m_pop.at(i);
	    break;
	  }
	}
	rank++;
      }
//       std::cout << "lol 3" << std::endl;
      if(m1!=nullptr && m2!=nullptr && m3 !=nullptr){
	      crossover(m1,m2,m3);
	      m1=nullptr;
	      m2=nullptr;
	      m3=nullptr;
      }
    } 
//     std::cout << "crossover ok, mutation" << std::endl;
    mutatePop();
    totalfitness=0.0;
    for (std::vector<Minion*>::iterator it = m_pop.begin(); it !=  m_pop.end(); ++it) {
	    evaluate(*it);																		// evaluation fitness
	    totalfitness+=(*it)->getFitness();
    }
//     std::cout << "mutation ok" << std::endl;
    std::cout << "Fitness moyenne après itération: " << totalfitness / m_pop.size() << std::endl;
//     std::cout << "population = " << m_pop.size() << std::endl;
}
