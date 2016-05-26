#include <iostream>
#include "controller.h"

int main(int argc, char **argv) {
    Controller* controller = Controller::create();
    try{
      
      controller->initiateRules("../regle.xml");
      controller->initiateMap("../map.txt");
//       std::cout << "init map & règles OK" << std::endl;
      controller->creer_agent(5,5,"Cavalier",0);
      controller->creer_agent(4,4,"Cavalier",1);
      controller->creer_agent(20,20,"Artillerie",2);
      controller->creer_agent(180,2,"Cavalier",3);
      controller->creer_agent(179,3,"Infanterie",4);
      
      controller->create_algogen();
      int x0,y0,x1,y1,x2,y2,x3,y3,x4,y4;
      x0=180;
      y0=190;
      x1=100;
      y1=150;
      x2=179;
      y2=168;
      x3=10;
      y3=175;
      x4=5;
      y4=199;
      
      controller->demande_chemin_algogen(0,x0,y0);
      controller->demande_chemin_algogen(1,x1,y1);
      controller->demande_chemin_algogen(2,x2,y2);	
      controller->demande_chemin_algogen(3,x3,y3);
      controller->demande_chemin_algogen(4,x4,y4);
      while(1){
	controller->tic();
	usleep(1000);
	controller->toc();
	if(controller->proch_case(0).first==x0 && controller->proch_case(0).second==y0 && // POURRI, A REFAIRE
	  controller->proch_case(1).first==x1 && controller->proch_case(1).second==y1 && 
	  controller->proch_case(2).first==x2 && controller->proch_case(2).second==y2 &&
	  controller->proch_case(3).first==x3 && controller->proch_case(3).second==y3 &&
	  controller->proch_case(4).first==x4 && controller->proch_case(4).second==y4 
	){
	  break;
	}else{
	  controller->deplacement_agent(0,controller->proch_case(0).first,controller->proch_case(0).second);
	  controller->deplacement_agent(1,controller->proch_case(1).first,controller->proch_case(1).second);
	  controller->deplacement_agent(2,controller->proch_case(2).first,controller->proch_case(2).second);
	  controller->deplacement_agent(3,controller->proch_case(3).first,controller->proch_case(3).second);
	  controller->deplacement_agent(4,controller->proch_case(4).first,controller->proch_case(4).second);
	}
      }/*
      	std::cout << "x0 :" << controller->proch_case(0).first << " y0 : " << controller->proch_case(0).second << std::endl;
	std::cout << "x1 :" << controller->proch_case(1).first << " y1 : " << controller->proch_case(1).second << std::endl;
	std::cout << " x2 :" << controller->proch_case(2).first << " y2 : " << controller->proch_case(2).second <<  std::endl;
	std::cout << " x3 :" << controller->proch_case(3).first << " y3 : " << controller->proch_case(3).second <<  std::endl;
	std::cout << " x4 :" << controller->proch_case(4).first << " y4 : " << controller->proch_case(4).second << std::endl;*/
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
