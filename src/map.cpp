#include "map.h"

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

Map::~Map()
{

}

Map* Map::create(int _w, int _h)
{
  if(m_map==nullptr){
    m_map = new Map(_w,_h);
    return m_map;
  }else{
    throw new str_exception("Une map existe déjà.");
  }
}

void Map::addTerrain(const std::string& _type, std::vector< std::pair< std::string, float > > & _contraintes_defaut)
{
  for(unsigned int i=0;i<m_terrains.size();++i){
    if(m_terrains.at(i)->getType()==_type){
      throw new str_exception("Le terrain '" + _type + "' existe déjà");
    }
  }
  m_terrains.push_back(new Terrain(_type,_contraintes_defaut));
}

void Map::addTerrain(const std::string& _type, std::vector< std::pair< std::string, float > > & _contraintes_defaut, bool _obstacle)
{
  for(unsigned int i=0;i<m_terrains.size();++i){
    if(m_terrains.at(i)->getType()==_type){
      throw new str_exception("Le terrain '" + _type + "' existe déjà");
    }
  }
  m_terrains.push_back(new Terrain(_type,_contraintes_defaut,_obstacle));
}

void Map::addUnite(const std::string& _type, std::vector< std::pair< std::string const &, float > >& _vitesse_d, 
		   std::vector< std::pair< std::string const &, float > >& _consoContraintes)
{
  for(unsigned int i=0;i<m_unites.size();++i){
    if(m_unites.at(i)->getType()==_type){
      throw new str_exception("Le type d'unité '" + _type + "' existe déjà");
    }
  }
  std::vector< std::pair<Terrain*, float> > vec_vit;
  std::vector< std::pair<Contrainte*, float> > vec_cont;
  for(unsigned int i=0;i<_vitesse_d.size();++i){			// creation du vecteur de vitesses
    Terrain * t = this->get_Terrain(_vitesse_d.at(i).first);
    vec_vit.push_back(t,_vitesse_d.at(i).second);
  }
  for(unsigned int i=0;i<_consoContraintes.size();++i){			// creation du vecteur de contraintes
    Contrainte * t = this->get_Contrainte(_vitesse_d.at(i).first);
    vec_vit.push_back(t,_consoContraintes.at(i).second);
  }
  m_unites.push_back(new Unite(_type,vec_vit,vec_cont));
}


void Map::addAgent(int _iden, int _x, int _y, std::string _unite)
{
  if(m_agents.size()<_iden){
    m_agents.resize(_iden+5);
  }
  Case * caseptr = m_sommets.at((_x*m_h)+_y);
  Unite * uniteptr;
  for(unsigned int i=0;i<m_unites.size();++i){
    if(m_unites.at(i)->getType()==_unite){
      uniteptr=m_unites.at(i);
      break;
    }
  }
  if(caseptr==nullptr||uniteptr==nullptr){
    throw new str_exception("Impossible de créer l'agent '" + std::to_string(_iden) +"': coordonnées ou type d'unité non valides");
  }else{
    m_agents.at(_iden)=new Agent(_iden,caseptr,uniteptr);
  }
}

void Map::addContrainte(std::string const & _contrainte)
{
  for(unsigned int i=0;i<m_contraintes.size();++i){
    if(m_contraintes.at(i)->getType()==_contrainte){
      throw new str_exception("La contrainte '" + _contrainte + "' existe déjà");
    }
  }
  m_terrains.push_back(new Contrainte(_contrainte));
}

void Map::move_agent(int id, int x, int y)
{
	if (id > m_agents.size())
		throw new str_exception("Cette unité n'existe pas");
	else
	{
		if (m_agents[id]==NULL)
			throw new str_exception("Cette unité n'existe plus");
		else
			m_agents[id]->setCase(this.get_Case(x,y));
	}
}

void Map::suppr_agent(int id)
{
	if (m_agents[id]==NULL)
		throw new str_exception("Cette unité n'existe plus");
	else
		m_agents[id]=NULL;
}

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

Agent* Map::get_Agents(int id) const
{
	if (id > m_agents.size())
		throw new str_exception("Cette unité n'existe pas");
	else
	{
		if (m_agents[id]==NULL)
			throw new str_exception("Cette unité n'existe plus");
		else
			return m_agents[id];
	}
}

Terrain* Map::get_Terrain(const std::string& _terrName) const
{
  for(unsigned int j=0;j<m_terrains.size();++i){
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
  for(unsigned int j=0;j<m_contraintes.size();++i){
    if(m_contraintes.at(j)->getNom()==_contrName){
      return m_contraintes.at(j);
    }
  }
  throw new str_exception("Erreur: la contrainte '" + _contrName + "' n'existe pas.");
}
