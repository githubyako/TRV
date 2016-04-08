#ifndef TERRAIN_H
#define TERRAIN_H
#include <string>
#include <vector>
#include "str_exception.h"
class Terrain{
private:
  std::string m_type;
  std::vector<std::pair<Contrainte*, float> > m_contraintes_defaut;
  bool m_obstacle;
public:
  Terrain(std::string & _type, std::vector<std::pair<Contrainte*, float> > _contraintes_defaut, bool _obstacle);
  Terrain(std::string & _type, std::vector<std::pair<Contrainte*, float> > _contraintes_defaut);
  ~Terrain();
  
  std::string const & getType() const;
  float getContrainteDef(Contrainte*) const;
  bool isObstacle() const;
};
#endif
