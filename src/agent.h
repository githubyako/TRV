#ifndef AGENT_H
#define AGENT_H

#include "unite.h"
#include "case.h"

class Agent{
  
private:
  int id;
  float multiplicateur_v;
  Unite *_unite;
  Case *_case;
  
  void setCase(Case* _c);
  void setUnite(Unite* _u);
  
public:
  Agent(int _iden, Case* _c, Unite* _u);
  int getId() const;
  float getMultiplicateurV() const;
  const Case* getCase() const;
  const Unite* getUnite() const;
 
  
  
};
#endif