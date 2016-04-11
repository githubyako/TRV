#include "map.h"
Map * Map::m_map;
// *************
// Constructeurs
// *************

Map::Map()
{

}

Map::Map(const Map& _map)
{

}

Map::Map(int _w, int _h):m_w(_w),m_h(_h),m_sommets()
{
  int casenum=0;
  for(int i=0;i<_w;++i){
    for(int j=0;j<_h;++j){
      m_sommets.insert( std::pair<int, Case*>(casenum++,new Case(_w,_h,(i*_h)+_w,m_terrains.at(0))) );
    }
  }
}

// ************
// Destructeurs
// ************

Map::~Map()
{

}

Map* Map::create(int _w, int _h)
{
  if(Map::m_map==nullptr){
    Map::m_map = new Map(_w,_h);
    return Map::m_map;
  }else{
    throw new str_exception("Une map existe déjà.");
  }
}

// Fonction d'ajout de Terrain (sans précision d'obstacle) à la map

void Map::addTerrain(const std::string& _type, std::vector< std::pair<std::string const &, float > > & _contraintes_defaut)
{
  // On regarde si le terrain existe déjà au vector m_terrains de la map
  std::vector< std::pair<Contrainte*, float> > vec_cont;
  for(unsigned int i=0;i<m_terrains.size();++i){
    if(m_terrains.at(i)->getType()==_type){
      // Si oui, on lève une exception
      throw new str_exception("Le terrain '" + _type + "' existe déjà");
    }
  }
  // Si non, on créé une nouvelle pair à ajouter au vector m_terrains
  for(unsigned int i=0;i<_contraintes_defaut.size();++i){			// creation du vecteur de contraintes
    Contrainte * t = this->get_Contrainte(_contraintes_defaut.at(i).first);
    vec_cont.push_back(std::make_pair(t,_contraintes_defaut.at(i).second));
  }
  m_terrains.push_back(new Terrain(_type,vec_cont));
}

// Fonction d'ajout de Terrain (avec précision d'obstacle) à la map

void Map::addTerrain(const std::string& _type, std::vector< std::pair<std::string const &, float > > & _contraintes_defaut, bool _obstacle)
{
  // On regarde si le terrain existe déjà au vector m_terrains de la map
  std::vector< std::pair<Contrainte*, float> > vec_cont;
  for(unsigned int i=0;i<m_terrains.size();++i){
    if(m_terrains.at(i)->getType()==_type){
      // Si oui, on lève une exception
      throw new str_exception("Le terrain '" + _type + "' existe déjà");
    }
  }
  // Si non, on créé une nouvelle pair à ajouter au vector m_terrains
  for(unsigned int i=0;i<_contraintes_defaut.size();++i){			// creation du vecteur de contraintes
    Contrainte * t = this->get_Contrainte(_contraintes_defaut.at(i).first);
    vec_cont.push_back(std::make_pair(t,_contraintes_defaut.at(i).second));
  }
  m_terrains.push_back(new Terrain(_type,vec_cont,_obstacle));
}

// Fonction d'ajout d'Unité à la map

void Map::addUnite(const std::string& _type, std::vector< std::pair< std::string const &, float > >& _vitesse_d, 
		   std::vector< std::pair< std::string const &, float > >& _consoContraintes)
{
  // On regarde si l'unité existe déjà au vector m_terrains de la map
  for(unsigned int i=0;i<m_unites.size();++i){
    if(m_unites.at(i)->getType()==_type){
      // Si oui, on lève une exception
      throw new str_exception("Le type d'unité '" + _type + "' existe déjà");
    }
  }
  // Si non, on construit la nouvelle unité puis on l'ajoute au vector m_unites
  std::vector< std::pair<Terrain*, float> > vec_vit;
  std::vector< std::pair<Contrainte*, float> > vec_cont;
  for(unsigned int i=0;i<_vitesse_d.size();++i){			// creation du vecteur de vitesses
    Terrain * t = this->get_Terrain(_vitesse_d.at(i).first);
    vec_vit.push_back(std::pair<Terrain*, float>(t,_vitesse_d.at(i).second));
  }
  for(unsigned int i=0;i<_consoContraintes.size();++i){			// creation du vecteur de contraintes
    Contrainte * t = this->get_Contrainte(_consoContraintes.at(i).first);
    vec_cont.push_back(std::pair<Contrainte*, float>(t,_consoContraintes.at(i).second));
  }
  m_unites.push_back(new Unite(_type,vec_vit,vec_cont));
}

// Fonction d'ajout d'un agent à la map
void Map::addAgent(int _iden, int _x, int _y, std::string const & _unite)
{
  // On aggrandit le vector m_agents s'il n'y a pas assez de place
  unsigned int id = (unsigned int) _iden;
  if(m_agents.size()<id){
    m_agents.resize(id+5);
  }
  // On récupère le pointeur vers la case de coordonnée x,y du vector m_sommets de la map
  Case * caseptr = m_sommets.at((_x*m_h)+_y);
  Unite * uniteptr = nullptr;
  // On récupère l'unité de nom _unite avec le vector m_unites de map
  for(unsigned int i=0;i<m_unites.size();++i){
    if(m_unites.at(i)->getType()==_unite){
      uniteptr=m_unites.at(i);
      break;
    }
  }
  // On regarde si la case et l'unité existe dans les différents vector de la map
  if(caseptr==nullptr||uniteptr==nullptr){
    // Si non, on lève une exception
    throw new str_exception("Impossible de créer l'agent '" + std::to_string(id) +"': coordonnées ou type d'unité non valides");
  }else{
    // Si oui, on créer et rajoute le nouvelle agent
    m_agents.at(id)=new Agent(id,caseptr,uniteptr);
  }
}

// Fonction d'ajout d'une Contrainte à la map
void Map::addContrainte(std::string const & _contrainte)
{
  // On regarde si la contrainte existe déjà au vector m_terrains de la map
  for(unsigned int i=0;i<m_contraintes.size();++i){
    if(m_contraintes.at(i)->getNom()==_contrainte){
      // Si oui, on lève une exception
      throw new str_exception("La contrainte '" + _contrainte + "' existe déjà");
    }
  }
  // Si non, on créer et rajoute une nouvelle contrainte
  m_contraintes.push_back(new Contrainte(_contrainte));
}

// Fonction pour la déplacement d'un agent d'identifiant id et à la "position" id du vector m_agents vers la case de coordonnées x,y
void Map::move_agent(int id, int x, int y)
{
  // On recherche si l'agent existe dans le vector m_agnets de la map
  unsigned int id2 = (unsigned int) id;
	if (id2 > m_agents.size())
		// Si non, on lève une excpetion
		throw new str_exception("Cette unité n'existe pas");
	// Si oui
	else
	{
		// On regarde si l'unité existe encore
		if (m_agents[id2]==NULL)
			// Si non, on lève une exception
			throw new str_exception("Cette unité n'existe plus");
		else
			// Si oui, on change la case de l'unité
			m_agents[id2]->setCase(Map::m_map->get_Case(x,y));
	}
}

// Fonction pour la suppresion d'un agent d'identifiant id et à la "position" id du vector m_agents
void Map::suppr_agent(int id)
{
  unsigned int id2 = (unsigned int) id;
        // On regarde si l'unité existe encore 
	if (m_agents[id2]==NULL)
		// Si non, on lève une exception
		throw new str_exception("Cette unité n'existe plus");
	else
		// Si oui, on mets le pointeur à NULL
		m_agents[id2]=NULL;
}

// ********
// Getteurs
// ********

int Map::get_m_h() const
{
  return m_h;
}

int Map::get_m_w() const
{
  return m_w;
}

Case* Map::get_Case(int _x, int _y) const
{
  return m_sommets.at((_x*m_h)+_y);
}

Agent* Map::get_Agent(int id) const
{
  unsigned int id2 = (unsigned int) id;
	if (id2 > m_agents.size())
		throw new str_exception("Cette unité n'existe pas");
	else
	{
		if (m_agents[id2]==NULL)
			throw new str_exception("Cette unité n'existe plus");
		else
			return m_agents[id2];
	}
}

Terrain* Map::get_Terrain(const std::string& _terrName) const
{
  for(unsigned int j=0;j<m_terrains.size();++j){
    if(m_terrains.at(j)->getType()==_terrName){
      return m_terrains.at(j);
    }
  }
  throw new str_exception("Erreur: le terrain '" + _terrName + "' n'existe pas.");
}

void Map::set_Terrain(int _x, int _y, const std::string& _terrName)
{
  Case * c = this->get_Case(_x,_y);
  Terrain * t = this->get_Terrain(_terrName);
  c->setTerrain(t);
}

Contrainte* Map::get_Contrainte(const std::string& _contrName) const
{
  for(unsigned int j=0;j<m_contraintes.size();++j){
    if(m_contraintes.at(j)->getNom()==_contrName){
      return m_contraintes.at(j);
    }
  }
  throw new str_exception("Erreur: la contrainte '" + _contrName + "' n'existe pas.");
}

void Map::set_Obstacle(int _x, int _y, int obst)
{
  Case * c = this->get_Case(_x,_y);
  if (obst == 0)
    c->setObstacle(false);
  else
    c->setObstacle(true);
}

