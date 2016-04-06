#ifndef UNITE_H
#define UNITE_H
#include <string>
#include <vector>
#include "terrain.h"

class Unite{
private:
  std::string m_type;
  std::vector< std::pair<Terrain*,float> > m_vitesse_d;
  std::vector< std::pair<std::string, float> > m_consoRessources;
  Unite();
public:

  Unite(Unite const & _unite);
  Unite(std::string const & _type, std::vector< std::pair<Terrain*,float> > _vitesse_d,std::vector< std::pair<std::string, float> > _consoRessources);
  std::string const & getType();
  float getVitesse(Terrain*);
  float getConso(std::string const & _ressource);
  ~Unite();
};

#endif