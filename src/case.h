#ifndef CASE_H
#define CASE_H
#include <map>
#include "terrain.h"
#include "contrainte.h"
#include <vector>

// Classe représentant une case de la Map

class Case{
  
private:
  unsigned int m_x,m_y; // Coordonnée x et y
  std::vector<std::pair<Contrainte*,float> >m_contraintes; // Contrainte (ex: ressource : avoine, blé...)
  std::vector<Case*> m_cases_vois;
  bool m_obstacle; // Booléen si la case est, ou non, franchissable
  unsigned int m_somm; // Numéro du sommet associé à cette case dans le graphe
  Terrain * m_terrain; // Pointeur vers le terrain qu'est la case
  
  static unsigned int id_somm;
  
  // Constructeurs :
  Case();
  Case(Case const & _case);
  
public:

  // Constructeur 
  Case(int _x, int _y, int _somm, Terrain * _terrain);
  
  // Getteurs
  unsigned int getX() const;
  unsigned int getY() const;
  unsigned int get_sommet() const;
  float getContrainte(Contrainte* _contrainte) const;
  const Terrain & getTerrain() const;
  bool isObstacle() const;
  
  // Setteurs
  void setObstacle(bool _b);
  void setTerrain(Terrain* _terrain);
  void setContrainte(std::vector<std::pair<Contrainte*,float> > _contr);
  void setContrainte(Contrainte* _contrainte,float _qte);
};
#endif
