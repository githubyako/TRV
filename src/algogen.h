#ifndef ALGOGEN_H
#define ALGOGEN_H

#include <vector>
#include <algorithm>
#include <iostream>

#include "map.h"

class Algogen{
private:
  Map * m_map;

public:
  Algogen(Map * _map);
  std::vector<int> const & findPath(int _idAgent, int _caseCible);
//   Case* recurse(int _idAgent, Case const* _case);
};
#endif