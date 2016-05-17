#include <iostream>
#include "controller.h"

int main(int argc, char **argv) {
    std::cout << "TRV" << std::endl;
    Controller* controller = Controller::create();
    try{
      
      controller->initiateRules("../regle.xml");
      controller->initiateMap("../map.txt");
      std::cout << "init map & règles OK" << std::endl;
      controller->creer_agent(5,5,"Cavalier",0);
      controller->creer_agent(4,4,"Cavalier",1);
      controller->creer_agent(300,300,"Artillerie",2);
      controller->creer_agent(5,450,"Infanterie",3);
      controller->creer_agent(4,5,"Cavalier",4);
      controller->creer_agent(310,310,"Cavalier",5);
      controller->creer_agent(400,250,"Infanterie",6);
      std::cout << "créations ok" << std::endl;
      controller->test();
      controller->create_algogen();
      controller->demande_chemin_algogen(0,400,400);
      controller->demande_chemin_algogen(1,400,400);
      controller->demande_chemin_algogen(2,4,4);
      controller->demande_chemin_algogen(3,450,5);
      controller->demande_chemin_algogen(4,400,400);
      controller->demande_chemin_algogen(5,4,4);
      controller->demande_chemin_algogen(6,1,1);
      controller->iterate_algogen(2000);
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
