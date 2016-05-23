#ifndef CONTRAINTE_H
#define CONTRAINTE_H
#include <string>

// Classe représentant une contrainte (ex : ressource : avoine, blén...)

class Contrainte{
private:
  std::string m_nom; // Nom de la contrainte
  
  // Constructeurs : private pour rendre inaccessible
  Contrainte();
  Contrainte(Contrainte const & _contrainte); 
public:
  
  // Constructeur
  Contrainte(std::string const & _nom); // seul constructeur qui servira
  
  // Destructeur
  ~Contrainte();
  
  // Getteur
  std::string const & getNom() const;
  
};
#endif
