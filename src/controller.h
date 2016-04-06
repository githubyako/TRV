#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <mutex>
#include <thread>
#include <unistd.h>
#include "str_exception.h"

// classe réalisée avec le design pattern "singleton"
class Controller{
private:
  static Controller * s_controller;
  Controller();
  Controller(Controller const & _controller);
  
public:
  ~Controller();
  static Controller * create();
  // ici, méthode de parsing du fichier txt
};

#endif
