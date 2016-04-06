#include "agent.h"


const Case* Agent::getCase() const
{
  return _case;
}

int Agent::getId() const
{
  return id;
}

float Agent::getMultiplicateurV() const
{
  return multiplicateur_v;
}

const Unite* Agent::getUnite() const
{
  return _unite;
}

void Agent::setCase(Case* _c)
{
  _case = _c;
}

void Agent::setUnite(Unite* _u)
{
  _unite = _u;
}


Agent::Agent(int _iden, Case* _c, Unite* _u): id(_iden), _case(_c), _unite(_u), multiplicateur_v(1.0)
{

}

