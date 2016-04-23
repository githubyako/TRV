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
      controller->creer_agent(2,1,"Artillerie",2);
      controller->creer_agent(14,6,"Infanterie",3);
      controller->test();
      controller->supprimer_agent(1);
      //controller->test();
     controller->deplacement_agent(0, 4, 1);
     // controller->test();
//      std::cout << "Déplacement cavalerie Dijkstra : 4,1 jusqu'à : 12,8 " << std::endl;
//      controller->demande_chemin(0,99,88);
     std::cout << "Déplacement cavalerie A* : 4,1 jusqu'à : 12,8 " << std::endl;
     controller->demande_chemin_A_star(0,99,88);
    } catch(str_exception& e){
    
      std::cout << "str_exception" << e.what() << std::endl;
    }
    catch(std::exception& e1)
    {
      std::cout << e1.what() << std::endl;
    }
    
    return 0;
}
