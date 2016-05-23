#include "contrainte.h"

// *************
// Constructeurs
// *************

Contrainte::Contrainte(const std::string& _nom)
:m_nom(_nom)
{}

Contrainte::Contrainte(const Contrainte& _contrainte)
{}

Contrainte::Contrainte()
{}

// ***********
// Destructeur
// ***********

Contrainte::~Contrainte()
{}

// *******
// Getteur
// *******

std::string const & Contrainte::getNom() const
{
  return m_nom;
}
