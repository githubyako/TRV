#ifndef AGENT_H
#define AGENT_H

#include "unite.h"
#include "case.h"

// Classe représentant les agents se déplaçant sur la Map

class Agent{
  
private:
  int m_id; // Identificateur d'un agent
  float m_multiplicateur_v; // Multiplicateur de vitesse de l'agent (fatigue, moral, ...)
  Unite *m_unite; // Pointeur vers l'unité qu'il est
  Case *m_case; // Pointeur vers la case où il se trouve

  
public:
  Agent(int _iden, Case* _c, Unite* _u); // Constructeur
  
  // Getteurs
  
  int getId() const;
  float getMultiplicateurV() const;
  const Case* getCase() const;
  const Unite* getUnite() const;
  
  // Setteurs
 
  void setCase(Case* _c);
  void setUnite(Unite* _u);  
  
};
#endif
