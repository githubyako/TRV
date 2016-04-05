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