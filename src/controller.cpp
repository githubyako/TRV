#include "controller.h"

Controller::Controller()
{
  // création des pipes entrants ? IL FAUT CHOISIR CLASSE INTERFACE OU THREAD+PIPES
  int creation_unite[2],;
  pipe(creation_unite);
  
  // création du pipe sortant
}

Controller::Controller(const Controller& _controller)
{
  
}

Controller* Controller::create()
{
  if(s_controller!=nullptr){
    throw new str_exception("An instance of controller already exists");
  }else{
    s_controller = new Controller();
    // thread?
    return s_controller;
  }
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
  //Parse fichier .txt du contenu de la carte
}

void Controller::initiateRules(std::string xmlFileName)
{
  //Parse fichier .xml des règles de la carte
}


Controller::~Controller()
{

}
