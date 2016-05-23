#include "unite.h"

// *************
// Constructeurs
// *************

Unite::Unite(const std::string& _type, std::vector< std::pair< Terrain*, float > > _vitesse_d, 
	     std::vector< std::pair< Contrainte*, float > > _consoContraintes)
:m_type(_type),m_vitesse_d(_vitesse_d),m_consoContraintes(_consoContraintes)
{
  float vitessemax=0.0;
  for(unsigned int i=0;i<m_vitesse_d.size();i++){
    vitessemax = std::max(vitessemax,m_vitesse_d.at(i).second);
  }
  m_vitesseMax = vitessemax;
}

Unite::Unite()
{

}

Unite::Unite(const Unite& _unite)
{
  
}

// ************
// Destructeurs
// ************

Unite::~Unite()
{

}

// ********
// Getteurs
// ********

const std::string& Unite::getType() const
{
  return m_type;
}

float Unite::getConso(Contrainte * _contrainte) const
{
  float result=0.0;
  // On recherche la contrainte _contrainte dans le vecteur m_consoContraintes de l'unité
  for(unsigned int i=0;i<m_consoContraintes.size();++i){
    if(m_consoContraintes.at(i).first==_contrainte){
      result=m_consoContraintes.at(i).second;
      break;
    }
  }
  return result;
}

float Unite::getVitesse(const Terrain& _terrain) const
{
  float result=0.0;
  // On recherche le terrain _terrain dans le vecteur m_vitesse_d de l'unité
  for(unsigned int i=0;i<m_vitesse_d.size();++i){
    if(m_vitesse_d.at(i).first->getType()==_terrain.getType()){
      result=m_vitesse_d.at(i).second;
      break;
    }
  }
  return result;
}

float Unite::getVitesseMax() const
{
  return m_vitesseMax;
}

