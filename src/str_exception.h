#ifndef HWEXCEPTION_H
#define HWEXCEPTION_H
#include <exception>
#include <string>

class str_exception:public std::exception{
private:
  std::string m_errmsg;  
  

public:
  str_exception(std::string _errmsg);
  std::string const what();
};
#endif
