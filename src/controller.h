#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <fstream>
#include <mutex>
#include <thread>
#include <unistd.h>
#include <iostream>
#include "str_exception.h"
#include "map.h"
#include <libxml++/libxml++.h>

// classe réalisée avec le design pattern "singleton"
class Controller{
private:
  static Controller * s_controller;
  Controller();
  Controller(Controller const & _controller);
  
  Map* map;
  
public:
  ~Controller();
  static Controller * create();
  void creer_agent(int x, int y, const std::string type, int id);
  void supprimer_agent(int id);
  void deplacement_agent(int id, int x, int y);
  void setObstacle(int x, int y, bool obs);
  void demande_chemin(int id, int x, int y);
  void initiateRules(std::string xmlFileName);
  void initiateMap(const std::string & contentFileName);
  std::vector<std::string> split(std::string str, char delimiter);
};

#endif
