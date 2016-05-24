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
      controller->creer_agent(480,2,"Cavalier",3);
      controller->creer_agent(479,3,"Infanterie",4);
      controller->creer_agent(2,2,"Artillerie",5);
      controller->create_algogen();
      controller->demande_chemin_algogen(0,50,50); // 5,5 -> 400,400
      for(unsigned int i=0;i<5000;++i){
	controller->tic();
	usleep(1000);
	controller->toc();
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
	if(i==40){
	  controller->demande_chemin_algogen(3,5,475);
	  controller->demande_chemin_algogen(5,356,498);
	}
	if(i>40){
	  std::cout << "Agent 3: " << controller->proch_case(3).first << " " << controller->proch_case(3).second << std::endl;
	  controller->deplacement_agent(3,controller->proch_case(3).first,controller->proch_case(3).second);
	  std::cout << "Agent 5: " << controller->proch_case(5).first << " " << controller->proch_case(5).second << std::endl;
	  controller->deplacement_agent(5,controller->proch_case(5).first,controller->proch_case(5).second);
	}
	if(i==50){
	  controller->demande_chemin_algogen(4,5,475);
	}
	if(i>50){
	  std::cout << "Agent 4: " << controller->proch_case(4).first << " " << controller->proch_case(4).second << std::endl;
	  controller->deplacement_agent(4,controller->proch_case(4).first,controller->proch_case(4).second);
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
