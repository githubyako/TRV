#include "LectMap.h"

LectMap::LectMap(const std::string& F)
{
  int x;
  int y;
  std::string type_terr;
  std::string contrainte ="";
  std::string::size_type sz;
  int obst=0;
  int i;
  std::vector<std::string> splitter;
  std::ifstream fichier (F.c_str(), std::ios::in);
  if(fichier)
  {
    std::string contenu;
    std::getline(fichier, contenu);
    splitter = split(contenu, ' ');
    x = atoi(splitter[0].c_str());
    y = atoi(splitter[1].c_str());
    //Map M(x,y);
    while (std::getline(fichier, contenu))
    {
      splitter.clear();
      splitter = split(contenu, ' ');  
      x = atoi(splitter[0].c_str());
      y = atoi(splitter[1].c_str());
      type_terr = splitter[2];
      switch (splitter.size())
      {
	case 4:
	  contrainte = splitter[3];
	  //M.getCase(x,y).setContrainte(contrainte);
	  break;
	case 5:
	  contrainte = splitter[3];
	  obst = atoi(splitter[4].c_str());
	  //M.getCase(x,y).setContrainte(contrainte);
	  //M.getCase(x,y).setObstacle(obst);
	  break;
      }
      //M.getCase(x,y).setTerrain(M.getTerrain(type_terr));
      /*std::cout << x << std::endl;
      std::cout << y << std::endl;
      std::cout << type_terr << std::endl;
      std::cout << contrainte << std::endl;
      std::cout << obst << std::endl;*/
    }
    fichier.close();
  }
   else
   {
     std::cout << "Impossible d'ouvrir le fichier !" << std::endl;
   }
}

std::vector< std::string > LectMap::split(std::string str, char delimiter)
{
  std::vector<std::string> internal;
  std::stringstream ss(str);
  std::string tok;
  
  while(std::getline(ss, tok, delimiter))
  {
    internal.push_back(tok);
  }
  return internal;
}


