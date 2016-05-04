#include "algogen.h"

Algogen::Algogen(int map_w, int map_h, const std::map< int, Case* >* _sommets, unsigned int _popsize, float _manhattanImportance, float _mutationRatio, float _popToMutate, unsigned int _nbAjouts, float _ratioSupprs, float _ratioModifs, float _ratioElitism, float _cullRatio, unsigned int _nbkids):
m_president(nullptr),m_superman(nullptr),m_ratioElitism(_ratioElitism)
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
  m_nbkidstotal=0;
  m_nbIterations=0;
}

void Algogen::initPop(int _caseSource, int _caseCible, const Unite* _typeAgent)
{
  m_unite.push_back(_typeAgent);
  m_orig.push_back(m_sommets->at(_caseSource));
  m_cible.push_back(m_sommets->at(_caseCible));
  unsigned int originX = m_orig[0]->getX();
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
    for(unsigned int i=0;i<8;i++){			// creation pop initiale
      	// ALEATOIRE ET COURT, A AMELIORER VIA ASTAR_GA
      if(i<3 && Astar){
	if (!(genome=Map::m_map->A_star_GA(_caseSource, ((originX+3*(b-e+2*(c-f)))*m_mapH+(originY+3*(e-b+2*(f-a)))), nullptr)).empty())
	{
	  m_pop.push_back(new SurMinion(lol));
	  m_pop.at(i)->addMinion(new Minion(genome));
	  i++;
	  genome.clear();
	}
	if (!(genome=Map::m_map->A_star_GA(_caseSource, ((originX+3*((a-c)*(1-e)+2*(c-a)))*m_mapH+(originY+3*((d-f)*(1-b)+2*(e-a-b-c+2*f)))), nullptr)).empty())
	{
	  m_pop.push_back(new SurMinion(lol));
	  m_pop.at(i)->addMinion(new Minion(genome));
	  i++;
	  genome.clear();
	}
	if (!(genome=Map::m_map->A_star_GA(_caseSource, ((originX+3*(b-e+2*(c-f)))*m_mapH+(originY+3*(e-b+2*(f-a)))), nullptr)).empty())
	{
	  m_pop.push_back(new SurMinion(lol));
	  m_pop.at(i)->addMinion(new Minion(genome));
	  i++;
	  genome.clear();
	}
      }
      Astar=false;
      if(!Astar){
	for(int j=0;j<6;++j){
	  bool bool1 = rand() % 2;
	  bool bool2 = rand() % 2;
	  genome.push_back(new std::pair<bool,bool>(bool1,bool2));
	}
      }
      m_pop.push_back(new SurMinion(lol));
      m_pop.at(i)->addMinion(new Minion(genome));
      genome.clear();
    }
  float totalfitness=0.0;
  for (std::vector<SurMinion*>::iterator it = m_pop.begin(); it !=  m_pop.end(); ++it) {
    evaluate(*it);						// evaluation fitness
    totalfitness+=(*it)->getFitness();
  }
  m_generationTotalFitness.push_back(totalfitness / m_pop.size());						// ajout au tableau de la fitness générale
}

Algogen::~Algogen()
{
    for (std::vector<SurMinion*>::iterator it = m_pop.begin(); it !=  m_pop.end(); ++it) {
        delete *it;
    }
}

void Algogen::crossover(SurMinion* _parent0, SurMinion* _parent1, SurMinion* _parent2)
{
  unsigned int iterations = _parent0->getMinions().size();
  for(unsigned int i=0;i<iterations;++i){
    Minion* g0 = _parent0->getMinion(i),*g1 = _parent1->getMinion(i),*g2=_parent2->getMinion(i);
    unsigned int nbchrs=std::max(std::max(g0->getGenomeSize(),g1->getGenomeSize()),g2->getGenomeSize());
    unsigned int parent;
    std::vector<Minion*> parents{g0,g1,g2};
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
	  for(std::vector<std::pair< bool, bool >* >::iterator cit = genome.begin(); cit != genome.end(); ++cit, tmps++){ // parcours du chemin pour détection d'obstacle
	    newx += ((*cit)->second*(1-(2*(*cit)->first)));
	    newy += (((*cit)->second -1) * ((2*(*cit)->first)-1));
	    sommet = (newx*m_mapH) + newy;
	    if (newx < 0 || newx > m_mapW-1 || newy < 0 || newy > m_mapH-1 || m_sommets->at(sommet)->isObstacle()){
	      newx -= ((*cit)->second*(1-(2*(*cit)->first)));
	      newy -= (((*cit)->second -1) * ((2*(*cit)->first)-1));
	      cit=genome.erase(cit);
	      sommet = (newx*m_mapH) + newy;
	      cit--;
	    } else {
	    int pos = std::distance(vec.begin(),std::find(vec.begin(), vec.end(), sommet));
	      if ((std::find(vec.begin(), vec.end(), sommet) != vec.end())) {
		int pos = std::distance(vec.begin(),std::find(vec.begin(), vec.end(), sommet));
		vec.erase(vec.begin()+pos+1, vec.end());
		couts.erase(couts.begin()+pos+1,couts.end());
		cout=*(couts.begin()+pos);
		cit=genome.erase(genome.begin()+pos, cit+1);
		cit--;
	      }else {
		if(sommet == m_cible.at(numAgent)->get_sommet()){
		  genome.erase(cit+1,genome.end());
		  vec.erase(vec.begin()+pos, vec.end());
		  couts.erase(couts.begin()+pos,couts.end());
		  cout=couts.back();
		  _vaChemin=true;
		  break;}
		vec.push_back(sommet);
		cout+=m_unite.at(numAgent)->getVitesse(m_sommets->at(sommet)->getTerrain());
		couts.push_back(cout);
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
      fitnessSM = (float)(fitnessM / (float) _surminion->getMinions().size());
      _surminion->setFitness(fitnessSM);
      _surminion->setVaChemin(_vaCheminSM);
      if (_vaCheminSM && (m_president==nullptr || !(m_president->getVaChemin()) || m_president->getFitness()>fitnessSM))
	 m_president=_surminion;
      else if ( !_vaCheminSM && (m_president==nullptr || (((!m_president->getVaChemin())) && (fitnessSM < m_president->getFitness()))))
	m_president=_surminion;
}


void Algogen::iterate()
{

    mutatePop();
    if(m_generationTotalFitness.size()>2 && m_generationTotalFitness.back() > *(m_generationTotalFitness.end()-1)){	// Si la fitness générale s'améliore, diminution du taux de mutation
      m_ratioSupprs = m_ratioSupprs * 0.99;
      m_ratioModifs = m_ratioModifs * 0.99;
    }else{
      m_ratioSupprs = m_ratioSupprs * 1.01;
      m_ratioModifs = m_ratioModifs * 1.01;
    }
    std::sort (m_pop.begin(), m_pop.end()); 		// tri
    SurMinion *sm1=nullptr, *sm2=nullptr, *sm3=nullptr;
    while(m_pop.size()<m_popsize){		// reproduction par rank selection exponentielle tant que la population n'a pas atteint m_popsize
//       if(m_pop.size() < 3){
// 	initPop(m_orig[0]->get_sommet(),m_cible[0]->get_sommet());
//       }
      
      if(m_superman!=nullptr && m_pop.back()->getFitness() < m_superman->getFitness()){
	std::vector<Minion*> superman = m_pop.front()->getMinions();		// création du superman (supersurminion)
	for(unsigned int i = 1;i<m_pop.size();i++){
	  for(unsigned int j=0;j<superman.size();j++){
	    if(m_pop.at(i)->getMinion(j)->getFitness() < superman.at(j)->getFitness()){
	      superman.at(i) = m_pop.at(i)->getMinion(j);
	    }
	  }
	}
	m_pop.push_back(new SurMinion(superman));			// supersurminion ajouté à la pop
      }
      
      for (int i = m_pop.size()-1;i>=0;i--){			// probabilité de sélection: 1/2 pour le meilleur individu, 1/4, pour le suivant, 1/8 pour le 3me...
	if(rand()%m_pop.size() > ((1/(i+1)) *  m_pop.size())){
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
    float totalfitness=0.0;
    for (std::vector<SurMinion*>::iterator it = m_pop.begin(); it !=  m_pop.end(); ++it) {
	    evaluate(*it);																		// evaluation fitness
	    totalfitness+=(*it)->getFitness();
    }
    m_generationTotalFitness.push_back(totalfitness);
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

// void Algogen::show() const
// {
//   std::cout << std::endl << "*******************************************************" << std::endl;
//   std::cout << "Stats: " << std::endl;
//   std::cout << m_nbkidstotal << " enfants créés." << std::endl;
//   std::cout << m_nbIterations << " iterations." << std::endl;
//   
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
//   std::cout << "_______________________" << std::endl << "Fitness des minions" << std::endl;
//   for(unsigned int i=0;i<m_pop.size();++i){
//     std::cout << "ID " << m_pop.at(i)->getID() << ", fitness =" << m_pop.at(i)->getFitness() << ", taille genome = " << m_pop.at(i)->getGenomeSize() << std::endl; 
//   }
//   std::vector<std::pair<bool, bool> > const & presgen = m_president->getGenome();
//   std::cout << "_______________________" << std::endl << "Président (id=" << m_president->getID() << ", " << presgen.size() << "déplacements):" << std::endl;
//   int newx = (int)(m_orig->getX());
//   int newy = (int)(m_orig->getY());
//   for(std::vector< std::pair< bool, bool > >::const_iterator cit = presgen.begin(); cit != presgen.end(); ++cit){
//     newx += ((*cit).second*(1-(2*(*cit).first)));
//     newy += (((*cit).second -1) * ((2*(*cit).first)-1));
//     std::cout << "X= " << newx << ", Y= " << newy << " | ";
//   }
// }
// 
// unsigned int Algogen::get_pres_nbdeplace()
// {
//   return m_president->getGenomeSize();
// }