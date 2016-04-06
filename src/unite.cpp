#include "unite.h"

Unite::Unite(const std::string& _type, std::vector< std::pair< Terrain*, float > > _vitesse_d, std::vector< std::pair< std::string, float > > _consoRessources)
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

float Unite::getConso(const std::string& _ressource)
{
  
}

float Unite::getVitesse(Terrain*)
{

}

