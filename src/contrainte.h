#ifndef CONTRAINTE_H
#define CONTRAINTE_H
#include <string>
class Contrainte{
private:
  std::string m_nom;
  Contrainte(); // private pour rendre inaccessible
  Contrainte(Contrainte const & _contrainte); // private pour rendre inaccessible
public:
  

  Contrainte(std::string const & _nom); // seul constructeur qui servira
  ~Contrainte();
  
  std::string const & getNom() const;
  
};
#endif
