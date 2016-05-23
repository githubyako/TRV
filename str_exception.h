#ifndef HWEXCEPTION_H
#define HWEXCEPTION_H
#include <exception>
#include <string>

// Classe permettant de relever plus clairement les exceptions
class str_exception:public std::exception{
private:
  std::string m_errmsg;  // Message d'erreur
  

public:
  // Constructeur :
  str_exception(std::string _errmsg);
  
  // Méthode renvoyant m_errmsg
  std::string const what();
};
#endif
