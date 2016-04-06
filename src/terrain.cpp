#include "terrain.h"

Terrain::Terrain(std::string& _type, std::vector< std::pair< std::string, float > > _contraintes_defaut, bool _obstacle)
:m_type(_type),m_contraintes_defaut(_contraintes_defaut),m_obstacle(_obstacle)
{
  
}

Terrain::Terrain(std::string& _type, std::vector< std::pair< std::string, float > > _contraintes_defaut)
:m_type(_type), m_contraintes_defaut(_contraintes_defaut),m_obstacle(0)
{

}

Terrain::~Terrain()
{

}

float Terrain::getContrainteDef(const std::string& _nomContrainte)
{
  float result;
  for(int i=0;i<m_contraintes_defaut.size();++i){
    if(m_contraintes_defaut.at(i).first==_nomContrainte){
      return m_contraintes_defaut.at(i).second;
    }
  }
  throw new str_exception("Contrainte '" + _nomContrainte + "' non trouvée dans les valeurs par défaut pour le terrain " m_type);
}

const std::string& Terrain::getType()
{
  return m_type;
}


bool Terrain::isObstacle()
{
  return m_obstacle;
}
