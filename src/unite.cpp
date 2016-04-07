#include "unite.h"

Unite::Unite(const std::string& _type, std::vector< std::pair< Terrain*, float > > _vitesse_d, 
	     std::vector< std::pair< Contrainte*, float > > _consoContraintes)
:m_type(_type),m_vitesse_d(_vitesse_d),m_consoContraintes(_consoContraintes)
{

}

Unite::Unite()
{

}

Unite::Unite(const Unite& _unite)
{
  
}

Unite::~Unite()
{

}

const std::string& Unite::getType()
{
  return m_type;
}

float Unite::getConso(Contrainte * _contrainte)
{
  float result=0.0;
  for(unsigned int i=0;i<m_consoContraintes.size();++i){
    if(m_consoContraintes.at(i).first==_contrainte){
      result=m_consoContraintes.at(i).second;
      break;
    }
  }
  return result;
}

float Unite::getVitesse(Terrain* _terrain)
{
  float result=0.0;
  for(unsigned int i=0;i<m_vitesse_d.size();++i){
    if(m_vitesse_d.at(i).first==_terrain){
      result=m_vitesse_d.at(i).second;
      break;
    }
  }
  return result;
}

