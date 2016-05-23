#include "terrain.h"

// *************
// Constructeurs
// *************

Terrain::Terrain(const std::string& _type, std::vector< std::pair< Contrainte*, float > > _contraintes_defaut, bool _obstacle)
:m_type(_type),m_contraintes_defaut(_contraintes_defaut),m_obstacle(_obstacle)
{
  
}

Terrain::Terrain(const std::string& _type, std::vector< std::pair< Contrainte*, float > > _contraintes_defaut)
:m_type(_type), m_contraintes_defaut(_contraintes_defaut),m_obstacle(0)
{

}

// ***********
// Destructeur
// ***********

Terrain::~Terrain()
{

}

// ********
// Getteurs
// ********

const std::vector< std::pair< Contrainte*, float > > Terrain::getContraintes() const
{
  return m_contraintes_defaut;
}


float Terrain::getContrainteDef(Contrainte* _contrName) const
{
  // On regarde si la contrainte _nomContrainte appartient au vector m_contraintes_defaut du terrain
  for(unsigned int i=0;i<m_contraintes_defaut.size();++i){
    if((m_contraintes_defaut.at(i).first)->getNom()==_contrName->getNom()){
      return m_contraintes_defaut.at(i).second;
    }
  }
  // Sinon, ce n'est pas normal, on lève donc une exception
  throw new str_exception("Contrainte '" + _contrName->getNom() + "' non trouvée dans les valeurs par défaut pour le terrain " + m_type);
  return 0.0;
}

const std::string& Terrain::getType() const
{
  return m_type;
}


bool Terrain::isObstacle() const
{
  return m_obstacle;
}
