#ifndef TERRAIN_H
#define TERRAIN_H
#include <string>
#include <vector>
#include "str_exception.h"
#include "contrainte.h"

// Classe représentant un type de terrain (instancié une et une seule fois lors du parsing des règles par type de terrain)

class Terrain{
private:
  std::string m_type; // Nom du type de terrain
  std::vector<std::pair<Contrainte*, float> > m_contraintes_defaut; // Vector de pair contrainte, float représentant le nombre (float) de contraintes par défaut sur le terrain (lors d'une initialisation d'une case avec un terrain sans spécifier de ressource)
  bool m_obstacle; // Booléen représentant si le terrain est, par défaut, franchissable ou non
public:

  // Constructeurs :
  Terrain(const std::string & _type, std::vector<std::pair<Contrainte*, float> > _contraintes_defaut, bool _obstacle);
  Terrain(const std::string & _type, std::vector<std::pair<Contrainte*, float> > _contraintes_defaut);
  
  // Destructeur :
  ~Terrain();
  
  // Getteur :
  std::string const & getType() const;
  const std::vector<std::pair<Contrainte*, fl_oat> > getContraintes() const;
  float getContrainteDef(Contrainte* _contrName) const;
  bool isObstacle() const;
};
#endif
