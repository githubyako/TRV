#include "algogen.h"

Algogen::Algogen(Map* _map, unsigned int _popsize, float _manhattanImportance, float _mutationRatio, float _popToMutate, float _ratioAjouts, 
				 float _ratioSupprs, float _ratioModifs, float _ratioElitism, float _cullRatio, unsigned int _nbkids):
m_map(_map),m_ratioElitism(_ratioElitism)
{
	if(0>_manhattanImportance || 0>_mutationRatio || 0>_popToMutate || 0>_ratioAjouts || 0>_ratioSupprs || 0>_ratioModifs || 0>_cullRatio
		|| _manhattanImportance>1 || _mutationRatio>1 || _popToMutate>1 || _ratioAjouts>1 || _ratioSupprs>1 || _ratioModifs>1 || _cullRatio>1){
		std::cerr << "Erreur: les ratios doivent être compris entre 0 et 1 inclus" << std::endl;
		throw str_exception("Erreur: les ratios doivent être compris entre 0 et 1 inclus");
	}else{
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
	initPop(m_orig->get_sommet(),m_cible->get_sommet());
}

void Algogen::initPop(int _caseSource, int _caseCible)
{
    m_orig=m_map->get_Case(_caseSource);
	m_cible=m_map->get_Case(_caseCible);
    unsigned int originX = m_orig->getX();
    unsigned int originY = m_orig->getY();

    // créer quelques minions avec dijkstra
    // et d'autres random
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
	for(unsigned int i=0;i<m_nbkids;++i){
		std::vector<std::pair<bool,bool> > kidgenome;
		for(unsigned int j=0;j<nbchrs;++j){
			parent = rand()%3;
			if(parent==0 && _parent0->getChromosome(j)!=nullptr){
				kidgenome.push_back(*(_parent0->getChromosome(j)));
			}else if(parent==1 && _parent1->getChromosome(j)!=nullptr){
				kidgenome.push_back(*(_parent1->getChromosome(j)));
			}else{
				kidgenome.push_back(*(_parent2->getChromosome(j)));
			}
		}
		m_pop.push_back(new Minion(kidgenome));
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
	unsigned int finRange = m_pop.size()/5;
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
	std::vector< std::pair< bool, bool > > const & genome = _minion->getGenome();
	int newx = (int)(m_orig->getX());
	int newy = (int)(m_orig->getY());
	bool defect = false;
	for(std::vector< std::pair< bool, bool > >::const_iterator cit = genome.begin(); cit != genome.end(); ++cit){ // parcours du chemin pour détection d'obstacle
		newx = (((*cit).first == 0 && (*cit).second == 0) || ((*cit).first == 1 && (*cit).second == 0)) ? newx : newx++ ;
		newy = ((*cit).second == 1) ? newy : newy++ ;
		if(m_map->get_Case(newx, newy)->isObstacle()){
			defect = true;
			break;
		}
	}
	if(!defect){
		int manhattan = (m_cible->getX() - m_map->get_Case(newx,newy)->getX()) + (m_cible->getY() - m_map->get_Case(newx,newy)->getY());
		fitness = 1 - (((manhattan / (m_map->get_m_w() + m_map->get_m_h())) * m_manhattanImportance) + ((genome.size() / (m_map->get_m_h() * m_map->get_m_w() )) * (1-m_manhattanImportance)));
	}
	_minion->setFitness(fitness);
}


void Algogen::iterate()
{
	float totalfitness=0.0;
	for (std::vector<Minion*>::iterator it = m_pop.begin(); it !=  m_pop.end(); ++it) {
		evaluate(*it);																		// evaluation fitness
		totalfitness+=(*it)->getFitness();
    }
    
    m_generationTotalFitness.push_back(totalfitness / m_pop.size());						// ajout au tableau de la fitness générale
	if(m_generationTotalFitness.back() > m_generationTotalFitness.back() - 1){				// Si la fitness générale s'améliore, diminution du taux de mutation
		m_ratioSupprs = m_ratioSupprs * 0.99;
		m_ratioModifs = m_ratioModifs * 0.99;
// 		m_ratioAjouts = m_ratioAjouts * 0.99; ?? bonne ou mauvaise idée?
	}
	
	std::sort (m_pop.begin(), m_pop.end()); 												// tri
	
	cull();																					// nettoyage
	
	m_lowestElite = (unsigned int)(m_pop.size() * (1 - m_ratioElitism));
	Minion *m1=nullptr, *m2=nullptr, *m3=nullptr;
	while(m_pop.size()<m_popsize){															// reproduction par rank selection exponentielle tant que la population n'a pas atteint m_popsize
		unsigned int rank = 1;																// création d'un couple:
		for (unsigned int i = m_pop.size()-1;i>=0;i--){										// probabilité de sélection: 1/2 pour le meilleur individu, 1/4, pour le suivant, 1/8 pour le 3me...
			if(rand()%m_pop.size() < (1/(2^rank)) * m_pop.size()){
				if(m1==nullptr) {m1=m_pop.at(i);
				}else if(m2==nullptr) {m2=m_pop.at(i);
				}else {m3=m_pop.at(i);}
			}
			rank++;
	    }
		if(m1!=nullptr && m2!=nullptr && m3 !=nullptr){
			crossover(m1,m2,m3);
			m1=nullptr;
			m2=nullptr;
			m3=nullptr;
		}
	}
	mutatePop();
}
