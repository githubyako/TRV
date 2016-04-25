#include "str_exception.h"

// *************
// Constructeurs
// *************

str_exception::str_exception(std::string _errmsg):m_errmsg(_errmsg)
{

}

// Méthode renvoyant m_errmsg

const std::string str_exception::what()
{
  return m_errmsg;
}
