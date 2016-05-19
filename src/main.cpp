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
      std::cout << "1" <<std::endl;
      controller->create_algogen();
      std::cout << "2" <<std::endl;
      controller->demande_chemin_algogen(0,400,400); // 5,5 -> 400,400
      std::cout << "3" <<std::endl;
      controller->tic();
      std::cout << "4" <<std::endl;
      controller->toc();
      std::cout << "5" <<std::endl;
//       std::cout << controller->proch_case(0).first << " " << controller->proch_case(0).second << std::endl;
//       controller->demande_chemin_algogen(2,4,4); // 300,300 -> 4,4
      controller->deplacement_agent(0,controller->proch_case(0).first,controller->proch_case(0).second);
      for(unsigned int i=0;i<100;++i){
	
	controller->tic();
	usleep(15000);
	controller->toc();
	std::cout << controller->proch_case(0).first << " " << controller->proch_case(0).second << std::endl;
	controller->deplacement_agent(0,controller->proch_case(0).first,controller->proch_case(0).second);
	
      }
      std::cout << "6" <<std::endl;
      controller->tic();
      controller->toc();
      std::cout << "7" <<std::endl;
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
