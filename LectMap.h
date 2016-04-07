#ifndef LectMap_h
#define LectMap_h
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
//#include "Map.h"
//#include "Case.h"

class LectMap
{
/*private:
  std::vector<Case*> Map;*/
  
public:
    LectMap(const std::string & F);
    std::vector<std::string> split(std::string str, char delimiter);
};
#endif