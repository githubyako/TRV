#include "controller.h"

Controller::Controller()
{
  // création des pipes entrants ? IL FAUT CHOISIR CLASSE INTERFACE OU THREAD+PIPES
  /*int creation_unite[2],;
  pipe(creation_unite);*/
  
  // création du pipe sortant
}

Controller::Controller(const Controller& _controller)
{
   
}

Controller* Controller::create()
{
  /*if(Controller::s_controller!=nullptr){
    throw new str_exception("An instance of controller already exists");
  }else{
    Controller::s_controller = new Controller();
    // thread?
    return Controller::s_controller;
  }*/
}


void Controller::setObstacle(int x, int y, bool obs)
{
  // Modifier les boolean de la case aux coordonnées x y
}

void Controller::creer_agent(int x, int y, std::string type, int id)
{
  //Créer agent à la case aux coordonnées x y, avec le type et l'id
}

void Controller::demande_chemin(int id, int x, int y)
{
}

void Controller::deplacement_agent(int id, int x, int y)
{

}

void Controller::supprimer_agent(int id)
{

}

void Controller::initiateMap(std::string contentFileName)
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
    Map M(x,y);
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
	  M.getCase(x,y).setContrainte(contrainte);
	  break;
	case 5:
	  contrainte = splitter[3];
	  obst = atoi(splitter[4].c_str());
	  M.getCase(x,y).setContrainte(contrainte);
	  M.getCase(x,y).setObstacle(obst);
	  break;
      }
      M.getCase(x,y).setTerrain(M.getTerrain(type_terr));
    }
    fichier.close();
  }
   else
   {
     std::cout << "Impossible d'ouvrir le fichier !" << std::endl;
   }
}

void Controller::initiateRules(std::string xmlFileName)
{
  //Parse fichier .xml des règles de la carte
  xmlpp::DomParser parser;
  parser.set_validate();
  parser.parse_file(xmlFileName);
  
  Node* rootNode = parser.get_document()->get_root_node();
  NodeSet contraintes = rootNode->find("/regle/contraintes");
  NodeSet terrains = rootNode->find("/regle/terrains");
  NodeSet unites = rootNode->find("/regle/unites");
  Node* firstNodeInResult = result.at(0);
  
}

std::vector< std::string > Controller::split(std::string str, char delimiter)
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


Controller::~Controller()
{

}
