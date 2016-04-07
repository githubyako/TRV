#include "map.h"

Map::Map()
{

}

Map::Map(const Map& _map)
{

}

Map::Map(int _w, int _h):m_sommets(),m_w(_w),m_h(_h)
{
  int casenum=0;
  for(int i=0;i<_w;++i){
    for(int j=0;j<_h;++j){
      m_sommets.insert( std::pair<int, Case*>(casenum++,new Case(_w,_h)) );
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
  for(int i=0;i<m_terrains.size();++i){
    if(m_terrains.at(i)->getType()==_type){
      throw new str_exception("Le terrain '" + _type + "' existe déjà");
    }
  }
  m_terrains.push_back(new Terrain(_type,_contraintes_defaut));
}

void Map::addTerrain(const std::string& _type, std::vector< std::pair< std::string, float > > & _contraintes_defaut, bool _obstacle)
{
  for(int i=0;i<m_terrains.size();++i){
    if(m_terrains.at(i)->getType()==_type){
      throw new str_exception("Le terrain '" + _type + "' existe déjà");
    }
  }
  m_terrains.push_back(new Terrain(_type,_contraintes_defaut,_obstacle));
}

void Map::addUnite(const std::string& _type, std::vector< std::pair< Terrain*, float > >& _vitesse_d, 
		   std::vector< std::pair< Contrainte*, float > >& _consoContraintes)
{
  for(int i=0;i<m_unites.size();++i){
    if(m_unites.at(i)->getType()==_type){
      throw new str_exception("Le type d'unité '" + _type + "' existe déjà");
    }
  }
  m_unites.push_back(new Unite(_type,_vitesse_d,_consoContraintes));
}


void Map::addAgent(int _iden, int _x, int _y, std::string _unite)
{
  if(m_agents.size()<_iden){
    m_agents.resize(_iden+5);
  }
  Case * caseptr = m_sommets.at((_x*m_h)+_y);
  Unite * uniteptr;
  for(int i=0;i<m_unites.size();++i){
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
  for(int i=0;i<m_contrainteNames.size();++i){
    if(m_contrainteNames.at(i)->getType()==_contrainte){
      throw new str_exception("La contrainte '" + _contrainte + "' existe déjà");
    }
  }
  m_terrains.push_back(new Contrainte(_contrainte));
}

int Map::get_m_h()
{
  return m_h;
}

int Map::get_m_w()
{
  return m_w;
}

Case* Map::get_Case(int _x, int _y)
{
  return m_sommets.at((_x*m_h)+_y);
}

std::vector< Agent* > Map::get_Agents()
{
  return m_agents;
}
