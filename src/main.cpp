#include <iostream>
#include "controller.h"

int main(int argc, char **argv) {
    std::cout << "TRV" << std::endl;
    Controller* controller = Controller::create();
    try{
      controller->initiateRules("regle.xml");
      controller->initiateMap("map.txt");
      controller->creer_agent(3,0,"Cavalier",0);
      controller->creer_agent(3,0,"Cavalier",1);
      controller->creer_agent(4,0,"Cavalier",0);
      controller->test();
      controller->supprimer_agent(1);
      controller->test();
      controller->deplacement_agent(0, 8, 12);
      controller->test();

    } catch(str_exception e){
    
      std::cout << e.what() << std::endl;
    }
    
    return 0;
}
