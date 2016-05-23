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
//       controller->creer_agent(5,450,"Infanterie",3);
//       controller->creer_agent(4,5,"Cavalier",4);
//       controller->creer_agent(310,310,"Cavalier",5);
//       controller->creer_agent(400,250,"Infanterie",6);
      controller->create_algogen();
      controller->demande_chemin_algogen(0,50,50); // 5,5 -> 400,400
      controller->tic();
      controller->toc();
//       std::cout << controller->proch_case(0).first << " " << controller->proch_case(0).second << std::endl;
//       controller->demande_chemin_algogen(2,4,4); // 300,300 -> 4,4
      controller->deplacement_agent(0,controller->proch_case(0).first,controller->proch_case(0).second);
      std::cout << "Agent 0: " << controller->proch_case(0).first << " " << controller->proch_case(0).second << std::endl;
      for(unsigned int i=0;i<5000;++i){
	controller->tic();
	std::cout << "apres tic" << std::endl;
	usleep(1000);
	controller->toc();
	std::cout << "apres toc" << std::endl;
	std::cout << "Agent 0: " << controller->proch_case(0).first << " " << controller->proch_case(0).second << std::endl;
	controller->deplacement_agent(0,controller->proch_case(0).first,controller->proch_case(0).second);
	if(i==20){
	  controller->demande_chemin_algogen(2,320,320);
	  controller->demande_chemin_algogen(1,50,50); // 5,5 -> 400,400
	}
	if(i>20){
	  std::cout << "Agent 1: " << controller->proch_case(1).first << " " << controller->proch_case(1).second << std::endl;
	  controller->deplacement_agent(1,controller->proch_case(1).first,controller->proch_case(1).second);
	  std::cout << "Agent 2: " << controller->proch_case(2).first << " " << controller->proch_case(2).second << std::endl;
	  controller->deplacement_agent(2,controller->proch_case(2).first,controller->proch_case(2).second);
	}
      }
      controller->tic();
      controller->toc();
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
