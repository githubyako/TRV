#ifndef AGENT_H
#define AGENT_H

#include "unite.h"
#include "case.h"

class Agent{
  
private:
  int m_id;
  float m_multiplicateur_v;
  Unite *m_unite;
  Case *m_case;
  
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
