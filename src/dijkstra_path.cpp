#include "dijkstra_path.h"

// Dijkstra_path::Dijkstra_path(const Dijkstra_path& _dp)
// {}
// 
// Dijkstra_path::Dijkstra_path()
// {}



Dijkstra_path::Dijkstra_path(Map* _map):m_map(_map),m_casenb(0),totalcost(0),m_casecible(nullptr),fini(false)
{
  unsigned int size = m_map->get_m_w() * m_map->get_m_h();
  for(unsigned int i = 0;i<size;++i){				// init des coûts à -1
    m_couts.insert(std::pair<int,float>(i, -1.0));
  }
  std::cout << "init ok" << std::endl;
}

std::vector< int > const& Dijkstra_path::findPath(int _idAgent, int _caseCible)
{
  std::cout << "test1" << std::endl;
  m_casecible = m_map->get_Case(_caseCible);
  std::cout << "test2" << std::endl;
//   Agent * ag = m_map->get_Agent(_idAgent);
  std::cout << "testlol" << std::endl;
  Case const * caseDepart= (m_map->get_Agent(_idAgent))->getCase(); 	// récupération pointeur case départ
  Case const * next;
  std::cout << "test3" << std::endl;
  m_couts.at(caseDepart->get_sommet())=0;			// init coût case départ à 0
  std::cout << "starting recurse" << std::endl;
  next = recurse(_idAgent,caseDepart);
  m_chemin.push_back(next->get_sommet());
  return m_chemin;
}

Case* Dijkstra_path::recurse(int _idAgent, Case const* _case)
{
  std::cout << "coucou, working on case " << _case->get_sommet() << std::endl;
  std::vector<Case*> vois=_case->getVois();
  for(std::vector<Case*>::const_iterator it = (_case->getVois()).begin();it!=(_case->getVois()).end();++it){ // for sur les voisins
    float newcout = m_couts.at((*it)->get_sommet()) = m_couts.at(_case->get_sommet()) +  ((m_map->get_Agent(_idAgent))->getUnite())->getVitesse(_case->getTerrain());
    if((m_couts.at((*it)->get_sommet()) == -1.0 || m_couts.at((*it)->get_sommet()) > newcout) && !(*it)->isObstacle()){ 	// ajout du nouveau coût si meilleur
      m_couts.at((*it)->get_sommet()) = newcout;
    }
  }
  for(std::vector<Case*>::const_iterator it = (_case->getVois()).begin();it!=(_case->getVois()).end();++it){ // for sur les voisins
    if(m_couts.at((*it)->get_sommet()) < totalcost && m_couts.at((*it)->get_sommet()) != -1.0){
      totalcost += m_couts.at((*it)->get_sommet());
      std::cout << "nouveau lowest cost = " << totalcost << std::endl;
    }
  }
  std::cout << "recherche plus petite case finie" << std::endl;
  Case* bestc=nullptr;
  while(!fini){
    int cout=999999;
    for(std::vector<Case*>::const_iterator it = vois.begin();it!=vois.end();++it){ // for sur les voisins
      cout = (cout > m_couts.at((*it)->get_sommet())) ? m_couts.at((*it)->get_sommet()) : cout;
      bestc = m_map->get_Case(m_couts.at((*it)->get_sommet()));
    }
    if(bestc != nullptr){
      m_chemin.push_back(bestc->get_sommet());
      if(bestc->get_sommet() == m_casecible->get_sommet()){
	fini=true;
	std::cout << "fini" << std::endl;
	return bestc;
      } else return recurse(_idAgent, bestc);
    }
  }
  /*
   *		RETURN INUTILISE CI DESSOUS: 
   */
  return bestc;
}