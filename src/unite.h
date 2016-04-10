#ifndef UNITE_H
#define UNITE_H
#include <string>
#include <vector>
#include "terrain.h"
#include "contrainte.h"

// Classe représentant un type d'unité (instancié une et une seule fois lors du parsing des règles par type d'unité)

class Unite{
private:
  std::string m_type; // Nom du type d'unité
  std::vector< std::pair<Terrain*,float> > m_vitesse_d; // Vector de pair prenant un terrain et un float, il représente le temps (float) que mets l'unité à traverser le terrain
  std::vector< std::pair<Contrainte*, float> > m_consoContraintes; // Vector de pair prenant une contrainte et un float, il représente la consommation (float) de la contrainte par l'unité
  
  // Constructeurs :
  Unite();
  Unite(Unite const & _unite);
public:

  // Constructeur
  Unite(std::string const & _type, std::vector< std::pair<Terrain*,float> > _vitesse_d,std::vector< std::pair<Contrainte*, float> > _consoContraintes);
  
  // Getteurs
  std::string const & getType() const;
  float getVitesse(Terrain* _terrain) const;
  float getConso(Contrainte * _contrainte) const;
  
  // Destructeur
  ~Unite();
};

#endif
