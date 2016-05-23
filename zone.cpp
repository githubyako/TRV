#include "zone.h"

unsigned int Zone::m_incrID=0;

Zone::Zone(unsigned int _caseOrig, unsigned int _leader, const std::vector< unsigned int > _cases, unsigned int _caseFin)
:m_caseOrig(_caseOrig), m_caseFin(_caseFin), m_leader(_leader), m_cases(_cases)
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

unsigned int Zone::get_leader() const
{
  return m_leader;
}

const std::vector< unsigned int >& Zone::get_cases() const
{
  return m_cases;
}

std::vector< std::pair< bool, bool >* > Zone::getDebutChemin() const
{
  return m_debutChemin;
}

void Zone::addDepl(std::pair< bool, bool >* _depl)
{
  if(_depl!=nullptr){
    m_debutChemin.push_back(new std::pair<bool,bool>(*_depl));
  }else{
    m_debutChemin.push_back(nullptr);
  }
}



Zone::~Zone()
{

}
