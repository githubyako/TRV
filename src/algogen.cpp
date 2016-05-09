#include "algogen.h"

Algogen::Algogen(int map_w, int map_h, const std::map< int, Case* >* _sommets, unsigned int _popsize, float _manhattanImportance, float _mutationRatio, float _popToMutate, unsigned int _nbAjouts, float _ratioSupprs, float _ratioModifs, float _ratioElitism, float _cullRatio, unsigned int _nbkids):
m_president(nullptr),m_superman(nullptr),m_ratioElitism(_ratioElitism)
{
  std::srand(std::time(0));
  if(0>_manhattanImportance || 0>_mutationRatio || 0>_popToMutate || 0>_nbAjouts || 0>_ratioSupprs || 0>_ratioModifs || 0>_cullRatio // Checking if arguments are in valid range (todo: factory)
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
  m_nbkidstotal=0;
  m_nbIterations=0;
}

void Algogen::initPop(int _caseSource, int _caseCible, const Unite* _typeAgent) // Creation of a new sub-population in each individual, at the request of demandeDéplacement()
{
  std::cout << "hoho 1" << std::endl;
  m_unite.push_back(_typeAgent);	// adding unit type to the relevant container
  m_orig.push_back(m_sommets->at(_caseSource)); // adding new path beginning to the relevant container
  m_cible.push_back(m_sommets->at(_caseCible)); // adding new path ending to the relevant container
  std::cout << "hoho 2" << std::endl;
  unsigned int originX = m_orig[0]->getX(); // gathering coordinates of those cells
  unsigned int originY = m_orig[0]->getY();
  unsigned int cibleX = m_cible[0]->getX();
  unsigned int cibleY = m_cible[0]->getY();
  int distanceX = originX - cibleX;
  int distanceY = originY - cibleY;
  bool a = cibleX < originX;
  bool b = cibleX == originX;
  bool c = 1-a-b;
  bool d = cibleY < originY;
  bool e = cibleY == originY;
  bool f = 1-d-e;
  bool Astar = ((std::abs(distanceY)>6) || (std::abs(distanceY)>3 && std::abs(distanceX)>3) || (std::abs(distanceX)>=6));
  std::vector<std::pair<bool,bool> *> genome;
  std::vector<Minion*> lol;
  std::cout << "hoho 3" << std::endl;
    for(unsigned int i=0;i<8;i++){ // base population consists of 8 total individuals
      if(i<3 && Astar){ // three of them are non-random, and calculated with the A* algorithm at 3 predefined points (one in a straight path, two at 45° angle from the straight path)
	if (!(genome=Map::m_map->A_star_GA(_caseSource, ((originX+3*(b-e+2*(c-f)))*m_mapH+(originY+3*(e-b+2*(f-a)))), nullptr)).empty()) // if the requested A* path is short enough (not calculated if too long)
	{
	  m_pop.push_back(new SurMinion(lol)); // A new individual is created. This instance regroups all requested paths.
	  m_pop.at(i)->addMinion(new Minion(genome)); // In this individual, a new path, as defined by A*, is created.
	  m_zones.push_back(std::pair<std::vector<Case*>,Case*>{m_sommets->at(_caseSource)->getVois(), m_sommets->at(_caseSource)}); // To handle multiple-units single-target movements, neighboring map cells are saved
	  i++;
	  genome.clear();
	}
	if (!(genome=Map::m_map->A_star_GA(_caseSource, ((originX+3*((a-c)*(1-e)+2*(c-a)))*m_mapH+(originY+3*((d-f)*(1-b)+2*(e-a-b-c+2*f)))), nullptr)).empty())
	{
	  m_pop.push_back(new SurMinion(lol)); // the above process is repeated for a different A* path
	  m_pop.at(i)->addMinion(new Minion(genome));
	  m_zones.push_back(std::pair<std::vector<Case*>,Case*>{m_sommets->at(_caseSource)->getVois(), m_sommets->at(_caseSource)});
	  i++;
	  genome.clear();
	}
	if (!(genome=Map::m_map->A_star_GA(_caseSource, ((originX+3*(b-e+2*(c-f)))*m_mapH+(originY+3*(e-b+2*(f-a)))), nullptr)).empty())
	{
	  m_pop.push_back(new SurMinion(lol)); // and then another
	  m_pop.at(i)->addMinion(new Minion(genome));
	  m_zones.push_back(std::pair<std::vector<Case*>,Case*>{m_sommets->at(_caseSource)->getVois(), m_sommets->at(_caseSource)});
	  i++;
	  genome.clear();
	}
      } // Once all three A* path definitions have been attempted...
      std::cout << "hoho 4" << std::endl;
      Astar=false;
      if(!Astar){
	for(int j=0;j<6;++j){ // We create the rest of the individuals by assigning them 6 random movements
	  bool bool1 = rand() % 2;
	  bool bool2 = rand() % 2;
	  genome.push_back(new std::pair<bool,bool>(bool1,bool2));
	}
      }
      std::cout << "hoho 5" << std::endl;
      m_pop.push_back(new SurMinion(lol));
      std::cout << "hoho 6" << std::endl;
      m_pop.at(i)->addMinion(new Minion(genome));
      std::cout << "hoho 7" << std::endl;
      m_zones.push_back(std::pair<std::vector<Case*>,Case*>{m_sommets->at(_caseSource)->getVois(), m_sommets->at(_caseSource)});
      std::cout << "hoho 8" << std::endl;
      genome.clear();
    }
  float totalfitness=0.0;
  std::cout << "hoho 9" << std::endl;
  for (std::vector<SurMinion*>::iterator it = m_pop.begin(); it !=  m_pop.end(); ++it) { // We then run the evaluation function
    std::cout << "hoho 9.5" << std::endl;
    evaluate(*it);
    std::cout << "hoho 10" << std::endl;
    totalfitness+=(*it)->getFitness();
    std::cout << "hoho 11" << std::endl;
  }
  std::cout << "hoho 12" << std::endl;
  m_generationTotalFitness.push_back(totalfitness / m_pop.size()); // An average fitness for this generation is then incorporated into the relevant container, for adaptive purposes
  std::cout << "hoho 13" << std::endl;
}

Algogen::~Algogen() // standard destructor, deleting all objects created in this class ('Minions' are in turn deleted by the Surminion class, which contains the pointers to them)
{
    for (std::vector<SurMinion*>::iterator it = m_pop.begin(); it !=  m_pop.end(); ++it) {
      delete *it;
    }
    for (std::vector<SousMinion*>::iterator it = m_sousMinions.begin(); it!= m_sousMinions.end(); ++it){
      delete *it;
    }
}

void Algogen::crossover(SurMinion* _parent0, SurMinion* _parent1, SurMinion* _parent2) // Creates new individuals based on the genome of three parents
{
  std::cout << "crossover appelé" << std::endl;
  unsigned int iterations = _parent0->getMinions().size();
  std::cout << "avant le for " << iterations << std::endl;
  for(unsigned int i=0;i<iterations;++i){
    std::cout << "lol1" << std::endl;
    Minion* g0 = _parent0->getMinion(i),*g1 = _parent1->getMinion(i),*g2=_parent2->getMinion(i);
    unsigned int nbchrs=std::max(std::max(g0->getGenomeSize(),g1->getGenomeSize()),g2->getGenomeSize());
    unsigned int parent;
    std::cout << "lol2" << std::endl;
    std::vector<Minion*> parents{g0,g1,g2};
    std::cout << "lol3" << std::endl;
    for(unsigned int i=0;i<m_nbkids;i++){
      std::vector<std::pair<bool,bool>*> kidgenome;
      for(unsigned int j=0;j<nbchrs;){
	parent = rand()%(parents.size());
	if(j >= parents.at(parent)->getGenomeSize()){
	  parents.erase(parents.begin() + parent);
	  continue;
	}else{
	  kidgenome.push_back(parents.at(parent)->getChromosome(j));
	  ++j;
	} 
      }
      m_pop.push_back(new SurMinion(std::vector<Minion*>{new Minion(kidgenome)}));
      m_nbkidstotal++;
    }
  }
}

void Algogen::cull()
{
    unsigned int finRange = (unsigned int)(m_pop.size()/5);
    float totalSupprs = (float)(finRange * m_cullRatio);
    float supprs=0.0;
    bool ded;
    while(supprs<totalSupprs){
	    for (std::vector<SurMinion*>::iterator it = m_pop.begin(); it !=  m_pop.end() - finRange;) {
		    ded = rand() % 2;
		    if(ded && supprs < totalSupprs && (*it)->getVaChemin()==false && (*it)->getID()!=m_president->getID()){
			    delete *it;
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
	  unsigned int SurMinionToMutate = rand() % m_pop.size();
	  elite = (SurMinionToMutate > m_lowestElite);
	  SurMinion* SM = m_pop.at(SurMinionToMutate);
	  if((m_president!=nullptr && SM->getID()!=m_president->getID()) || m_president==nullptr){
	    unsigned int nbrMinionsToMutate = SM->getNumberMinions() * m_mutationRatio;
	    std::vector<Minion*> minions = SM->getMinions();
	    for(unsigned int i = 0; i < nbrMinionsToMutate; i++){
	      unsigned int minionToMutate = rand()%(minions.size());
	      if(elite){
		std::swap(*(minions.begin()+minionToMutate),minions.back());
		minions.pop_back();
		SM->mutateElite(minionToMutate, m_nbAjouts,m_ratioModifs);
	      }else{
		std::swap(*(minions.begin()+minionToMutate),minions.back());
		minions.pop_back();
		SM->mutate(minionToMutate, m_nbAjouts, m_ratioSupprs,m_ratioModifs);
	      }
	    }
	  }
	}
}


void Algogen::evaluate(SurMinion* _surminion)
{
	float fitnessSM=0.0, fitnessM=0.0,cout;
	bool _vaCheminSM = true;
	unsigned int numAgent=0;
	int newx;
	int newy;
	unsigned int sommet;
	std::vector<int> vec;
	std::vector<float> couts;
	std::vector<std::pair<unsigned int, unsigned int>> vec_conf;
	unsigned int tmps;
	bool _vaChemin = false;
	bool ajout = false;
	std::cout << "mdr 1" << std::endl;
	for (std::vector<Minion*>::iterator it = _surminion->getMinions().begin(); it < _surminion->getMinions().end(); it++,numAgent++)
	{
	  vec.clear();
	  couts.clear();
	  vec_conf.clear();
	  fitnessM = 0;
	  cout = 0.0;
	  tmps=0;
	  newx = (int)(m_orig.at(numAgent)->getX());
	  newy = (int)(m_orig.at(numAgent)->getY());
	  sommet = (newx*m_mapH) + newy;
	  vec.push_back(sommet);
	  couts.push_back(0.0);
	  _vaChemin=false;
	  vec_conf.push_back(std::pair<unsigned int, unsigned int>(sommet, tmps));
	  std::vector<std::pair<bool,bool>*> genome = _surminion->getMinions().at(numAgent)->getGenome();
	  std::cout << "mdr 2" << std::endl;
	  for(std::vector<std::pair< bool, bool >* >::iterator cit = genome.begin(); cit != genome.end(); ++cit, tmps++){ // parcours du chemin pour détection d'obstacle
	    newx += ((*cit)->second*(1-(2*(*cit)->first)));
	    newy += (((*cit)->second -1) * ((2*(*cit)->first)-1));
	    sommet = (newx*m_mapH) + newy;
	    std::cout << "mdr 3" << std::endl;
	    if (newx < 0 || newx > m_mapW-1 || newy < 0 || newy > m_mapH-1 || m_sommets->at(sommet)->isObstacle()){
	      std::cout << "mdr 4" << std::endl;
	      newx -= ((*cit)->second*(1-(2*(*cit)->first)));
	      newy -= (((*cit)->second -1) * ((2*(*cit)->first)-1));
	      cit=genome.erase(cit);
	      sommet = (newx*m_mapH) + newy;
	      cit--;
	    } else {
	      std::cout << "mdr 4" << std::endl;
	      int pos = std::distance(vec.begin(),std::find(vec.begin(), vec.end(), sommet));
		if ((std::find(vec.begin(), vec.end(), sommet) != vec.end())) {
		  std::cout << "mdr 5" << std::endl;
		  int pos = std::distance(vec.begin(),std::find(vec.begin(), vec.end(), sommet));
		  vec.erase(vec.begin()+pos+1, vec.end());
		  couts.erase(couts.begin()+pos+1,couts.end());
		  cout=*(couts.begin()+pos);
		  cit=genome.erase(genome.begin()+pos, cit+1);
		  cit--;
		  while (vec_conf.back().first != sommet)
		  {
		    std::cout << "mdr 6" << std::endl;
		    vec_conf.pop_back();
		    tmps--;
		  }
		}else {
		  std::cout << "mdr 7" << std::endl;
		  if(sommet == m_cible.at(numAgent)->get_sommet()){
		    std::cout << "mdr 8" << std::endl;
		    genome.erase(cit+1,genome.end());
		    vec.erase(vec.begin()+pos, vec.end());
		    couts.erase(couts.begin()+pos,couts.end());
		    cout=couts.back();
		    _vaChemin=true;
		    break;
		  }
		  vec.push_back(sommet);
		  cout+=m_unite.at(numAgent)->getVitesse(m_sommets->at(sommet)->getTerrain());
		  couts.push_back(cout);
		  ajout=false;
		  while(!ajout)
		  {
		    std::cout << "mdr 9" << std::endl;
		    if ((std::find(vec_conf.begin(), vec_conf.end(), std::pair<unsigned int, unsigned int>(sommet, tmps)) == vec_conf.end()))
		    {
		      std::cout << "mdr 10" << std::endl;
		      vec_conf.push_back(std::pair<unsigned int, unsigned int>(sommet,tmps));
		      ajout = true;
		    }
		    else
		    {
		      std::cout << "mdr 11" << std::endl;
		      genome.insert(++cit,nullptr);
		      tmps++;
		    }
		  }
		}
	      }
	    }
	    (*it)->setSommetFinal(vec.back());
	    m_taillemax = std::max(m_taillemax,(unsigned int)genome.size());
	    (*it)->setVaChemin(_vaChemin);
	    if (_vaChemin == false)
	      _vaCheminSM = false;
	    int manhattan = 0.0;
	    if(_vaChemin){
	      fitnessM = (float)((float)cout + (float)genome.size());
	    }else{
	      int manhattan = abs(m_cible.at(numAgent)->getX() - m_sommets->at(vec.back())->getX()) + abs(m_cible.at(numAgent)->getY() - m_sommets->at(vec.back())->getY());
	      fitnessM = ((float)manhattan*m_manhattanImportance);
	    }
	    (*it)->setFitness(fitnessM);
	    (*it)->setManhattan(manhattan);
	    (*it)->setGenome(genome);
	    fitnessSM+=fitnessM;
	}
	fitnessSM = (float)(fitnessSM / (float) _surminion->getMinions().size());
	_surminion->setFitness(fitnessSM);
	_surminion->setVaChemin(_vaCheminSM);
	if (_vaCheminSM && (m_president==nullptr || !(m_president->getVaChemin()) || m_president->getFitness()>fitnessSM))
	{
	  m_president=_surminion;
	  m_conf_pres = vec_conf;
	}
	else if ( !_vaCheminSM && (m_president==nullptr || (((!m_president->getVaChemin())) && (fitnessSM < m_president->getFitness()))))
	{
	  m_president=_surminion;
	  m_conf_pres = vec_conf;
	}
}

void Algogen::evaluateSSM()
{
  std::vector<std::pair<unsigned int, unsigned int>> vec_conf;
  vec_conf = m_conf_pres;
  int numAgent=0;
  bool ajout;
  int newx;
  int newy;
  unsigned int sommet;
  unsigned int tmps =0;
  for (std::vector<SousMinion*>::iterator it = m_sousMinions.begin(); it < m_sousMinions.end(); it++, numAgent++)
  {
    ajout = false;
    tmps=0;
    newx = (int)(m_orig.at(numAgent)->getX());
    newy = (int)(m_orig.at(numAgent)->getY());
    sommet = (newx*m_mapH) + newy;
    std::vector<std::pair<bool,bool>*> genome = m_sousMinions.at(numAgent)->getGenome();
    for (std::vector<std::pair<bool,bool>*>::iterator cit = genome.begin(); cit < genome.end(); cit++)
    {
      newx += ((*cit)->second*(1-(2*(*cit)->first)));
      newy += (((*cit)->second -1) * ((2*(*cit)->first)-1));
      sommet = (newx*m_mapH) + newy;
      while(!ajout)
	{
	  if ((std::find(vec_conf.begin(), vec_conf.end(), std::pair<unsigned int, unsigned int>(sommet, tmps)) == vec_conf.end()))
	  {
	    vec_conf.push_back(std::pair<unsigned int, unsigned int>(sommet,tmps));
	    ajout = true;
	  }
	  else
	  {
	    genome.insert(++cit,nullptr);
	    tmps++;
	  }
	}
    }
  }
}

void Algogen::iterate()
{
    std::cout << "début itération" << std::endl;
    mutatePop();
    std::cout << "adaptation" << std::endl;
    if(m_generationTotalFitness.size()>2 && m_generationTotalFitness.back() > *(m_generationTotalFitness.end()-1)){	// Si la fitness générale s'améliore, diminution du taux de mutation
      m_ratioSupprs = m_ratioSupprs * 0.99;
      m_ratioModifs = m_ratioModifs * 0.99;
    }else{
      m_ratioSupprs = m_ratioSupprs * 1.01;
      m_ratioModifs = m_ratioModifs * 1.01;
    }
    std::cout << "tri" << std::endl;
    std::sort (m_pop.begin(), m_pop.end()); 		// tri
    SurMinion *sm1=nullptr, *sm2=nullptr, *sm3=nullptr;
    std::cout << "crossover" << std::endl;
    while(m_pop.size()<m_popsize){		// reproduction par rank selection exponentielle tant que la population n'a pas atteint m_popsize
//       if(m_pop.size() < 3){
// 	initPop(m_orig[0]->get_sommet(),m_cible[0]->get_sommet());
//       }
      std::cout << "crossover appelé (iterate)" << std::endl;
      if(m_superman==nullptr || m_pop.front()->getFitness() < m_superman->getFitness()){
	std::vector<Minion*> superman = m_pop.front()->getMinions();		// création du superman (supersurminion)
	for(unsigned int i = 1;i<m_pop.size();i++){
	  std::cout << "popsize = " << m_pop.size() << std::endl;
	  for(unsigned int j=0;j<superman.size();j++){
	    std::cout << "superman size = " << superman.size() << std::endl;
	    if(m_pop.at(i)->getMinion(j)->getFitness() < superman.at(j)->getFitness()){
	      superman.at(j) = m_pop.at(i)->getMinion(j);
	    }
	  }
	}
	m_pop.push_back(new SurMinion(superman));			// supersurminion ajouté à la pop
      }
      std::cout << "superman ok" << std::endl;
      for (int i = m_pop.size()-1;i>=0;--i){			// probabilité de sélection: 1/2 pour le meilleur individu, 1/4, pour le suivant, 1/8 pour le 3me...
	if((float)(rand()%m_pop.size()) > (float)((1/(i+1)) *  m_pop.size())){
	  if(sm1==nullptr) {sm1=m_pop.at(i);
	  }else if(sm2==nullptr && m_pop.at(i)!=sm1) {sm2=m_pop.at(i);
	  }else if(m_pop.at(i)!=sm1 && m_pop.at(i)!=sm2){sm3=m_pop.at(i);
	    break;
	  }
	}
      }
      if(sm1!=nullptr && sm2!=nullptr && sm3 !=nullptr){
	  crossover(sm1,sm2,sm3);
	  sm1=nullptr;
	  sm2=nullptr;
	  sm3=nullptr;
      }
    }
    std::cout << "eval" << std::endl;
    float totalfitness=0.0;
    for (std::vector<SurMinion*>::iterator it = m_pop.begin(); it !=  m_pop.end(); ++it) {
	    evaluate(*it);  // evaluation fitness
	    totalfitness+=(*it)->getFitness();
    }
    m_generationTotalFitness.push_back(totalfitness);
    std::cout << "cull" << std::endl;
    cull();
    m_nbIterations++;
}

// unsigned int Algogen::get_nb_goodResults()
// {
//   unsigned int result = 0;
//   for(unsigned int i=0;i<m_pop.size();i++){
//     if(m_pop.at(i)->getVaChemin()){
//       result++;
//     }
//   }
//   return result;
// }

void Algogen::show() const
{
  std::cout << std::endl << "*******************************************************" << std::endl;
  std::cout << "Stats: " << std::endl;
  std::cout << m_nbkidstotal << " enfants créés." << std::endl;
  std::cout << m_nbIterations << " iterations." << std::endl;
  
//   for(unsigned int i=0;i<m_pop.size();++i){
//     if(m_pop.at(i)->getVaChemin()){
//       std::vector< std::pair< bool, bool > > genome = m_pop.at(i)->getGenome();
//       std::cout << "Genome ayant trouvé le chemin (id=" << m_pop.at(i)->getID() << ", " << genome.size() << " éléments, fitness = " << m_pop.at(i)->getFitness() << ") : " << std::endl;
//       int newx = (int)(m_orig->getX());
//       int newy = (int)(m_orig->getY());
// //       unsigned int sommet = (newx*m_mapH) + newy;
//       for(std::vector< std::pair< bool, bool > >::iterator cit = genome.begin(); cit != genome.end(); ++cit){
// 	newx += ((*cit).second*(1-(2*(*cit).first)));
// 	newy += (((*cit).second -1) * ((2*(*cit).first)-1));
// 	std::cout << "X= " << newx << ", Y= " << newy << " | ";
//       }
//       std::cout << std::endl;
//     }
//   }
  std::cout << "_______________________" << std::endl << "Fitness des surminions" << std::endl;
  for(unsigned int i=0;i<m_pop.size();++i){
    std::cout << "ID " << m_pop.at(i)->getID() << ", fitness =" << m_pop.at(i)->getFitness() << std::endl; 
  }
  
  std::vector<std::pair<bool, bool> *> const & presgen;
  std::cout << "_______________________" << std::endl << "Président (id=" << m_president->getID() << std::endl;
  
  for(unsigned int i=0; i<m_president->getNumberMinions();++i){
    m_president->getMinion(i);
    std::cout << "Chemin " << i << ": taille genome = " << m_president->getMinion(i)->getGenomeSize() << ", vachemin = " << m_president->getMinion(i)->getVaChemin() << ", genome = " << std::endl;
    for(unsigned int j = 0; j<m_president->getMinion(i)->getGenomeSize();++j){
      std::pair<bool,bool> * chromo = m_president->getMinion(i)->getChromosome(j);
//       std::string str = 
    }
  }
  
  
  
  
  int newx = (int)(m_orig->getX());
  int newy = (int)(m_orig->getY());
  for(std::vector< std::pair< bool, bool > >::const_iterator cit = presgen.begin(); cit != presgen.end(); ++cit){
    newx += ((*cit).second*(1-(2*(*cit).first)));
    newy += (((*cit).second -1) * ((2*(*cit).first)-1));
    std::cout << "X= " << newx << ", Y= " << newy << " | ";
  }
}
// 
// unsigned int Algogen::get_pres_nbdeplace()
// {
//   return m_president->getGenomeSize();
// }

void Algogen::addDeplacement(int _idAgent, int _caseSource, int _caseCible, const Unite* _typeAgent)
{
  // vérification des zones etc
  std::cout << "haha1" << std::endl;
  unsigned int originX = m_sommets->at(_caseSource)->getX(); // x de la case source
  unsigned int originY = m_sommets->at(_caseSource)->getY(); // y de la case source
  std::cout << "haha2" << std::endl;
  bool newleader=true;
  // TO DO 
  
  for(unsigned int i=0;i<m_zones.size();i++){
    for(unsigned int j=0;j<m_zones.at(i).first.size();){
      std::cout << "haha3" << std::endl;
      unsigned int cibleX = m_sommets->at(m_zones.at(i).second->get_sommet())->getX(); // 
      unsigned int cibleY = m_sommets->at(m_zones.at(i).second->get_sommet())->getY(); // 
      std::cout << "haha4" << std::endl;
      if(m_zones.at(i).first.at(j)->get_sommet() == (unsigned int)_caseSource){ // si la case source du nouveau déplacement est trouvée dans une des zones...
	newleader=false;
	std::cout << "haha5" << std::endl;
	m_sousMinions.push_back(new SousMinion(_idAgent,std::vector<std::pair<bool,bool> *>{new std::pair<bool,bool>(originX>=cibleX && originY>=cibleY, cibleY>=originY && cibleX>originX)}));
	
// 	m_zones.at(i).
	// blabiblob gestion du rattrapage du chemin du minion en question (+gestion conflits? a voir)
      }
    }
  }
  std::cout << "haha6" << std::endl;
  if(newleader){
    initPop(_caseSource, _caseCible, _typeAgent);
  }
  std::cout << "haha7" << std::endl;
}
