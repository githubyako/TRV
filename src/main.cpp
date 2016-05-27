#include <iostream>
#include "controller.h"

int main(int argc, char **argv) {
    Controller* controller = Controller::create();
    try{
      controller->initiateRules("../regle.xml");
      controller->initiateMap("../mapGood/mapObstacle2.txt");
//       std::cout << "init map & règles OK" << std::endl;
      controller->creer_agent(25,10,"Cavalier",0);
      controller->creer_agent(10,190,"Cavalier",1);
      controller->creer_agent(10,180,"Artillerie",2);
      controller->creer_agent(175,175,"Cavalier",3);
      controller->creer_agent(75,25,"Infanterie",4);
      
      controller->create_algogen();
      
      int x0,y0,x1,y1,x2,y2,x3,y3,x4,y4;
//       std::cout << "init ok" << std::endl;
      x0=175;
      y0=175;
      x1=180;
      y1=180;
      x2=125;
      y2=10;
      x3=175;
      y3=175;
      x4=25;
      y4=10;
      
      controller->demande_chemin_algogen(0,x0,y0);
      controller->demande_chemin_algogen(1,x1,y1);
      controller->demande_chemin_algogen(2,x2,y2);	
      controller->demande_chemin_algogen(3,x3,y3);
      controller->demande_chemin_algogen(4,x4,y4);
      while(1){
	controller->tic();
	usleep(1000);
	controller->toc();
	if(controller->proch_case(0).first==x0 && controller->proch_case(0).second==y0 &&
	  controller->proch_case(1).first==x1 && controller->proch_case(1).second==y1 && 
	  controller->proch_case(2).first==x2 && controller->proch_case(2).second==y2 &&
	  controller->proch_case(3).first==x3 && controller->proch_case(3).second==y3 &&
	  controller->proch_case(4).first==x4 && controller->proch_case(4).second==y4 
	){
	  break;
	}else{
// 	      std::cout << "3 ";
// 	  std::cout << "x0 :" << controller->proch_case(0).first << " y0 : " << controller->proch_case(0).second << std::endl;
// 	            	std::cout << "x0 :" << controller->proch_case(0).first << " y0 : " << controller->proch_case(0).second << std::endl;
// 	std::cout << "x1 :" << controller->proch_case(1).first << " y1 : " << controller->proch_case(1).second << std::endl;
// 	std::cout << " x2 :" << controller->proch_case(2).first << " y2 : " << controller->proch_case(2).second <<  std::endl;
// 	std::cout << " x3 :" << controller->proch_case(3).first << " y3 : " << controller->proch_case(3).second <<  std::endl;
// 	std::cout << " x4 :" << controller->proch_case(4).first << " y4 : " << controller->proch_case(4).second << std::endl;
	  controller->deplacement_agent(0,controller->proch_case(0).first,controller->proch_case(0).second);
	  controller->deplacement_agent(1,controller->proch_case(1).first,controller->proch_case(1).second);
	  controller->deplacement_agent(2,controller->proch_case(2).first,controller->proch_case(2).second);
	  controller->deplacement_agent(3,controller->proch_case(3).first,controller->proch_case(3).second);
	  controller->deplacement_agent(4,controller->proch_case(4).first,controller->proch_case(4).second);
// 	      std::cout << "4 " << std::endl;;
	}
      }

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
