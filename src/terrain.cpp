#include "terrain.h"

Terrain::Terrain(std::string& _type, std::vector<std::pair<Contrainte*, float> > _contraintes_defaut, bool _obstacle)
:m_type(_type),m_contraintes_defaut(_contraintes_defaut),m_obstacle(_obstacle)
{
  
}

Terrain::Terrain(std::string& _type, std::vector<std::pair<Contrainte*, float> > _contraintes_defaut)
:m_type(_type), m_contraintes_defaut(_contraintes_defaut),m_obstacle(0)
{

}

Terrain::~Terrain()
{

}

float Terrain::getContrainteDef(Contrainte* _nomContrainte) const
{
  for(unsigned int i=0;i<m_contraintes_defaut.size();++i){
    if((m_contraintes_defaut.at(i).first)->getNom()==_nomContrainte->getNom()){
      return m_contraintes_defaut.at(i).second;
    }
  }
  throw new str_exception("Contrainte '" + _nomContrainte->getNom() + "' non trouvée dans les valeurs par défaut pour le terrain " + m_type);
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
