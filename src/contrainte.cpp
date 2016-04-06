#include "contrainte.h"

Contrainte::Contrainte(const std::string& _nom)
:m_nom(_nom)
{

}

Contrainte::Contrainte(const Contrainte& _contrainte)
{

}

Contrainte::Contrainte()
{

}

Contrainte::~Contrainte()
{

}

std::string const & Contrainte::getNom()
{
  return m_nom;
}
