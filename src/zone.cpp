#include "zone.h"

unsigned int Zone::m_incrID=0;

Zone::Zone(unsigned int _caseOrig, Minion* _leader, const std::vector< unsigned int > _cases)
:m_caseOrig(_caseOrig), m_caseFin(_leader->getSF()), m_leader(_leader), m_cases(_cases)
{
  m_numero=m_incrID++;
}

unsigned int Zone::get_orig() const
{
  return m_caseOrig;
}

unsigned int Zone::get_fin() const
{
  return m_caseFin;
}

Minion* Zone::get_leader() const
{
  return m_leader;
}

const std::vector< unsigned int >& Zone::get_cases() const
{
  return m_cases;
}


Zone::~Zone()
{

}
