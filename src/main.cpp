#include <iostream>
#include "controller.h"

int main(int argc, char **argv) {
    std::cout << "TRV" << std::endl;
    Controller* controller = Controller::create();
    try{
      
      controller->initiateRules("../regle.xml");
      controller->initiateMap("../map.txt");
      std::cout << "init map & règles OK" << std::endl;
      controller->creer_agent(3,0,"Cavalier",0);
      controller->creer_agent(4,4,"Cavalier",1);
      controller->creer_agent(4,5,"Cavalier",4);
      controller->creer_agent(2,1,"Artillerie",2);
      controller->creer_agent(14,6,"Infanterie",3);
      std::cout << "créations ok" << std::endl;
      controller->test();
      controller->create_algogen();
      controller->deplacement_agent(0, 5, 5);
      controller->deplacement_agent(3, 5, 95);
     // controller->test();
//      std::cout << "Déplacement cavalerie Dijkstra : 4,1 jusqu'à : 12,8 " << std::endl;
//      controller->demande_chemin(0,99,88);
//      controller->demande_chemin_A_star(0,450,450);
//      std::cout << "astar ok" << std::endl;
      controller->demande_chemin_algogen(0,90,90);
      controller->demande_chemin_algogen(3,95,5);
      controller->demande_chemin_algogen(1,90,90);
      controller->demande_chemin_algogen(4,90,90);
      controller->iterate_algogen(1000);
    } catch(str_exception& e){
    
      std::cout << "str_exception" << e.what() << std::endl;
    }
    catch(std::exception& e1)
    {
      std::cout << e1.what() << std::endl;
    }
    Controller::delete_controller();
    return 0;
}
