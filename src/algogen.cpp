#include "algogen.h"

Algogen::Algogen(int map_w, int map_h, const std::map< int, Case* >* _sommets, unsigned int _popsize, float _manhattanImportance, float _mutationRatio, float _popToMutate, unsigned int _nbAjouts, float _ratioSupprs, float _ratioModifs, float _ratioElitism, float _cullRatio, unsigned int _nbkids):
m_ratioElitism(_ratioElitism)
{
  std::srand(std::time(0));
  if(0>_manhattanImportance || 0>_mutationRatio || 0>_popToMutate || 0>_nbAjouts || 0>_ratioSupprs || 0>_ratioModifs || 0>_cullRatio
	  || _manhattanImportance>1 || _mutationRatio>1 || _popToMutate>1 || _ratioSupprs>1 || _ratioModifs>1 || _cullRatio>1){
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
	  m_nbAjouts=_nbAjouts;
	  m_ratioSupprs=_ratioSupprs;
	  m_ratioModifs=_ratioModifs;
	  m_cullRatio=_cullRatio;
	  m_nbkids=_nbkids;
  }
}

void Algogen::initPop(int _caseSource, int _caseCible)
{
  m_orig=m_sommets->at(_caseSource);
  m_cible=m_sommets->at(_caseCible);
  unsigned int originX = m_orig->getX();
  unsigned int originY = m_orig->getY();
  unsigned int cibleX = m_cible->getX();
  unsigned int cibleY = m_cible->getY();
  int distanceX = originX - cibleX;
  int distanceY = originY - cibleY;
  bool a = cibleX < originX;
  bool b = cibleX == originX;
  bool c = 1-a-b;
  bool d = cibleY < originY;
  bool e = cibleY == originY;
  bool f = 1-d-e;
  bool Astar = ((std::abs(distanceY)>6) || (std::abs(distanceY)>3 && std::abs(distanceX)>3) || (std::abs(distanceX)>=6));
    for(unsigned int i=0;i<8;i++){							// creation pop initiale::endl;
      std::vector<std::pair<bool,bool> > genome;
      if(i<3 && Astar){
	 m_pop.push_back(new Minion(Map::m_map->A_star_GA(_caseSource, ((originX+3*(b-e+2*(c-f)))*m_mapH+(originY+3*(e-b+2*(f-a)))), nullptr)));
	 m_pop.push_back(new Minion(Map::m_map->A_star_GA(_caseSource, ((originX+3*((a-c)*(1-e)+2*(c-a)))*m_mapH+(originY+3*((d-f)*(1-b)+2*(e-a-b-c+2*f)))), nullptr)));
	 m_pop.push_back(new Minion(Map::m_map->A_star_GA(_caseSource, ((originX+3*(e-b+2*(f-a)))*m_mapH+(originY+3*(e-b+2*(f-c)))), nullptr)));
	i += 3;
      }
      else{
      }
      if(!Astar){
	for(int j=0;j<5;++j){
	  bool bool1 = rand() % 2;
	  bool bool2 = rand() % 2;
	  genome.push_back(std::pair<bool,bool>(bool1,bool2));
	}
      }
      m_pop.push_back(new Minion(genome));
    }
  float totalfitness=0.0;
  for (std::vector<Minion*>::iterator it = m_pop.begin(); it !=  m_pop.end(); ++it) {
    evaluate(*it);						// evaluation fitness
    totalfitness+=(*it)->getFitness();
  }
  m_generationTotalFitness.push_back(totalfitness / m_pop.size());						// ajout au tableau de la fitness générale
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
  std::vector<Minion*> parents{_parent0,_parent1,_parent2};
  for(unsigned int i=0;i<m_nbkids;i++){
    std::vector<std::pair<bool,bool> > kidgenome;
    for(unsigned int j=0;j<nbchrs;){
      parent = rand()%(parents.size());
      if(j >= parents.at(parent)->getGenomeSize()){
	parents.erase(parents.begin() + parent);
	continue;
      }else{
	kidgenome.push_back(*(parents.at(parent)->getChromosome(j)));
	++j;
      } 
    }
    m_pop.push_back(new Minion(kidgenome));
//     std::cout << "taille du genome de l'enfant: " << kidgenome.size() << std::endl;
  }
}

void Algogen::cull()
{
    for (std::vector<Minion*>::iterator it = m_pop.begin(); it !=  m_pop.end();) {
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
			m_pop.at(MinionToMutate)->mutateElite(m_nbAjouts);
		}else{
			m_pop.at(MinionToMutate)->mutate(m_nbAjouts, m_ratioSupprs,m_ratioModifs);
		}
    }
}

void Algogen::evaluate(Minion* _minion)
{
	float fitness=0.0;
	std::vector< std::pair< bool, bool > > genome = _minion->getGenome();
	int newx = (int)(m_orig->getX());
	int newy = (int)(m_orig->getY());
	std::vector<int> vec;
	unsigned int sommet = (newx*m_mapH) + newy;
	vec.push_back(sommet);
	for(std::vector< std::pair< bool, bool > >::iterator cit = genome.begin(); cit != genome.end(); ++cit){ // parcours du chemin pour détection d'obstacle
	  newx += ((*cit).second*(1-(2*(*cit).first)));
	  newy += (((*cit).second -1) * ((2*(*cit).first)-1));
	  sommet = (newx*m_mapH) + newy;
	  
	  if (newx < 0 || newx > m_mapW-1 || newy < 0 || newy > m_mapH-1 || m_sommets->at(sommet)->isObstacle()){
	    newx -= ((*cit).second*(1-(2*(*cit).first)));
	    newy -= (((*cit).second -1) * ((2*(*cit).first)-1));
	    cit=genome.erase(cit);
// 	    std::cout << newx << " " << newy << std::endl;
	    sommet = (newx*m_mapH) + newy;
	    cit--;
	  } else {
	   int pos = std::distance(vec.begin(),std::find(vec.begin(), vec.end(), sommet));
	    if ((std::find(vec.begin(), vec.end(), sommet) != vec.end())) {
	      int pos = std::distance(vec.begin(),std::find(vec.begin(), vec.end(), sommet));
	      vec.erase(vec.begin()+pos+1, vec.end());
	      cit=genome.erase(genome.begin()+pos, cit+1);
	      
	      cit--;
	    }else {
	      if(sommet == m_cible->get_sommet()){
		genome.erase(cit,genome.end());
		vec.erase(vec.begin()+pos, vec.end());
		_minion->setVaChemin(true);
		break;
	      }
	      vec.push_back(sommet);
	    }
	   }
	 }
// 	 std::cout << sommet << std::endl;
	int manhattan = abs(m_cible->getX() - m_sommets->at(vec.back())->getX()) + abs(m_cible->getY() - m_sommets->at(vec.back())->getY());
	fitness = 1 - ((((float)manhattan / (m_mapW + m_mapH)) * m_manhattanImportance) + (((float)genome.size() / (m_mapH * m_mapW )) * (1-m_manhattanImportance)));
	_minion->setFitness(fitness);
	_minion->setManhattan(manhattan);
// 	std::cout << manhattan << std::endl;
	_minion->setGenome(genome);
}


void Algogen::iterate()
{

    mutatePop();
    if(m_generationTotalFitness.back() > m_generationTotalFitness.back() - 1){				// Si la fitness générale s'améliore, diminution du taux de mutation
      m_ratioSupprs = m_ratioSupprs * 0.99;
      m_ratioModifs = m_ratioModifs * 0.99;
    }
    std::sort (m_pop.begin(), m_pop.end()); 												// tri
    m_lowestElite = (unsigned int)(m_pop.size() * (1 - m_ratioElitism));
    Minion *m1=nullptr, *m2=nullptr, *m3=nullptr;
    while(m_pop.size()<m_popsize){		// reproduction par rank selection exponentielle tant que la population n'a pas atteint m_popsize
      if(m_pop.size() < 3){
	initPop(m_orig->get_sommet(),m_cible->get_sommet());
      }
      for (int i = m_pop.size()-1;i>=0;i--){					// probabilité de sélection: 1/2 pour le meilleur individu, 1/4, pour le suivant, 1/8 pour le 3me...
	if(rand()%m_pop.size() > ((1/(i+1)) *  m_pop.size())){
	  if(m1==nullptr) {m1=m_pop.at(i);
	  }else if(m2==nullptr && m_pop.at(i)!=m1) {m2=m_pop.at(i);
	  }else if(m_pop.at(i)!=m1 && m_pop.at(i)!=m2){m3=m_pop.at(i);
	    break;
	  }
	}
      }
      if(m1!=nullptr && m2!=nullptr && m3 !=nullptr){
	  crossover(m1,m2,m3);
	  m1=nullptr;
	  m2=nullptr;
	  m3=nullptr;
      }
    }
    float totalfitness=0.0;
    for (std::vector<Minion*>::iterator it = m_pop.begin(); it !=  m_pop.end(); ++it) {
	    evaluate(*it);																		// evaluation fitness
	    totalfitness+=(*it)->getFitness();
    }
    cull();
}

unsigned int Algogen::get_nb_goodResults()
{
  unsigned int result = 0;
  for(unsigned int i=0;i<m_pop.size();i++){
    if(m_pop.at(i)->getVaChemin()){
      result++;
    }
  }
  return result;
}

void Algogen::show() const
{
  std::cout << std::endl << "*******************************************************" << std::endl;
  std::cout << "Stats: " << std::endl;
  std::cout << m_nbkidstotal << " enfants créés." << std::endl;
  std::cout << m_nbIterations << " iterations." << std::endl;
  
  for(unsigned int i=0;i<m_pop.size();++i){
    if(m_pop.at(i)->getVaChemin()){
    std::cout << "Genome ayant trouvé le chemin: " << std::endl;
      std::vector< std::pair< bool, bool > > genome = m_pop.at(i)->getGenome();
      int newx = (int)(m_orig->getX());
      int newy = (int)(m_orig->getY());
      unsigned int sommet = (newx*m_mapH) + newy;
      for(std::vector< std::pair< bool, bool > >::iterator cit = genome.begin(); cit != genome.end(); ++cit){
	newx += ((*cit).second*(1-(2*(*cit).first)));
	newy += (((*cit).second -1) * ((2*(*cit).first)-1));
	std::cout << "X= " << newx << ", Y= " << newy << " | ";
      }
      std::cout << std::endl;
    }
  }
}
