#include "agent.h"


const Case* Agent::getCase() const
{
  return m_case;
}

int Agent::getId() const
{
  return m_id;
}

float Agent::getMultiplicateurV() const
{
  return m_multiplicateur_v;
}

const Unite* Agent::getUnite() const
{
  return m_unite;
}

void Agent::setCase(Case* _c)
{
  m_case = _c;
}

void Agent::setUnite(Unite* _u)
{
  m_unite = _u;
}


Agent::Agent(int _iden, Case* _c, Unite* _u): m_id(_iden), m_multiplicateur_v(1.0), m_unite(_u), m_case(_c)
{

}
