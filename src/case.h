#ifndef CASE_H
#define CASE_H
#include <map>
#include "terrain.h"

class Case{
  
private:
  unsigned int x;
  unsigned int y;
  std::map<std::string,float> contrainte_obs;
  bool obstacle;
  unsigned int somm;
  Terrain *terrain;
  
  static unsigned int id_somm;
  
  void setObstacle(bool b);
  void setTerrain(Terrain* terrain);
  void setContrainte_obs(std::string,float);
  
public:
  Case(int _x, int _y,
  unsigned int getX() const;
  unsigned int getY() const;
  float getContrainte(std::string ressource) const;
  const Terrain* getTerrain() const;
  bool isObstacle() const;
  
  
};
#endif