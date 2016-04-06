#include "unite.h"

Unite::Unite(const std::string& _type, std::vector< std::pair< Terrain*, float > > _vitesse_d, 
	     std::vector< std::pair< Contrainte*, float > > _consoContraintes)
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

float Unite::getConso(Contrainte const & _contrainte)
{
  
}

float Unite::getVitesse(Terrain*)
{

}

