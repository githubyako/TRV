#ifndef UNITE_H
#define UNITE_H
#include <string>
#include <vector>
#include "terrain.h"
#include "contrainte.h"
class Unite{
private:
  std::string m_type;
  std::vector< std::pair<Terrain*,float> > m_vitesse_d;
  std::vector< std::pair<std::string, float> > m_consoContraintes;
  Unite();
  Unite(Unite const & _unite);
public:

  Unite(std::string const & _type, std::vector< std::pair<Terrain*,float> > _vitesse_d,std::vector< std::pair<Contrainte*, float> > _consoContraintes);
  std::string const & getType();
  float getVitesse(Terrain*);
  float getConso(Contrainte const & _contrainte);
  ~Unite();
};

#endif