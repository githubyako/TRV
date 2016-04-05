#include "str_exception.h"

str_exception::str_exception(std::string _errmsg):m_errmsg(_errmsg)
{

}



const std::string str_exception::what()
{
  return m_errmsg;
}
